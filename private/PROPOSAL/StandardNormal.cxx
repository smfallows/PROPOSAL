/*! \file   StandardNormal.cxx
*   \brief  Source file for the standard normal routines.
*
*   For more details see the class documentation.
*
*   \date   02.08.2010
*   \author Jan-Hendrik Koehne
*/


#include "PROPOSAL/StandardNormal.h"
#include <algorithm>

using namespace std;


StandardNormal::StandardNormal()
    :val1_                  ( 0 )
    ,val2_                  ( 0 )
    ,do_interpolation_      ( false )
    ,norm_                  ( 1/sqrt(2*PI) )
    ,order_of_interpolation_( 5 )

{
    Init(5,20,1.e-6 );
    interpolant_ = new Interpolant();
}

//----------------------------------------------------------------------------//

StandardNormal::StandardNormal(const StandardNormal &normal)
    :integral_               ( new Integral(*normal.integral_) )
    ,interpolant_            ( new Interpolant(*normal.interpolant_) )
    ,val1_                   ( normal.val1_ )
    ,val2_                   ( normal.val2_ )
    ,do_interpolation_       ( normal.do_interpolation_ )
    ,norm_                   ( normal.norm_ )
    ,order_of_interpolation_ ( normal.order_of_interpolation_ )

{

}
//----------------------------------------------------------------------------//

StandardNormal& StandardNormal::operator=(const StandardNormal &normal){
    if (this != &normal)
    {
      StandardNormal tmp(normal);
      swap(tmp);
    }
    return *this;
}
//----------------------------------------------------------------------------//
bool StandardNormal::operator==(const StandardNormal &normal) const
{
    if (val1_                   != normal.val1_ )                   return false;
    if (val2_                   != normal.val2_ )                   return false;
    if (do_interpolation_       != normal.do_interpolation_ )       return false;
    if (norm_                   != normal.norm_ )                   return false;
    if (order_of_interpolation_ != normal.order_of_interpolation_ ) return false;
    if (*integral_              != *normal.integral_ )              return false;
    if (*interpolant_           != *normal.interpolant_ )           return false;

    //else
    return true;
}
//----------------------------------------------------------------------------//
bool StandardNormal::operator!=(const StandardNormal &normal) const
{
    return !(*this == normal);
}
//----------------------------------------------------------------------------//
void StandardNormal::swap(StandardNormal &normal)
{
    using std::swap;

    swap(val1_                   , normal.val1_ );
    swap(val2_                   , normal.val2_ );
    swap(do_interpolation_       , normal.do_interpolation_ );
    swap(norm_                   , normal.norm_ );
    swap(order_of_interpolation_ , normal.order_of_interpolation_ );
    swap(integral_               , normal.integral_ );
    swap(interpolant_            , normal.interpolant_ );
}

//----------------------------------------------------------------------------//

StandardNormal::StandardNormal(int romberg, int maxSteps, double precision)
    :val1_                  ( 0 )
    ,val2_                  ( 0 )
    ,do_interpolation_      ( false )
    ,norm_                  ( 1/sqrt(2*PI) )
    ,order_of_interpolation_( 5 )
{
    Init(romberg, maxSteps, precision);
    interpolant_ = new Interpolant();

}

//----------------------------------------------------------------------------//


void StandardNormal::Init(int romberg, int maxSteps, double precision)
{

    integral_    =   new Integral(romberg, maxSteps, precision);
    val1_        =   IntegratedProbability(-1);
    val2_        =   IntegratedProbability(1);

}

//----------------------------------------------------------------------------//

double StandardNormal::IntegratedProbability(double x)
{
    if(x<-5)
    {
        return 0;
    }
    else if(x>5)
    {
        return 1;
    }

    if(do_interpolation_)
    {
        return min(max(interpolant_->Interpolate(x), 0.0), 1.0);
    }

    if(x<=-1)
    {
        return integral_->Integrate(1 , x, boost::bind(&StandardNormal::FunctionToIntegral, this, _1),3, -2);
    }
    else if(x<=1)
    {
        return val1_ + integral_->Integrate(-1 , x, boost::bind(&StandardNormal::FunctionToIntegral, this, _1),2);
    }
    else
    {
        return val2_ + integral_->Integrate(1 , x, boost::bind(&StandardNormal::FunctionToIntegral, this, _1),3, 2);
    }
}

//----------------------------------------------------------------------------//

double StandardNormal::StandardNormalRandomNumber(double x)
{
    if(do_interpolation_)
    {
        return interpolant_->FindLimit(x);
    }
    if(x<=val1_)
    {
        integral_->IntegrateWithSubstitution(1 , -1, boost::bind(&StandardNormal::FunctionToIntegral, this, _1), -2, -x);
        return integral_->GetUpperLimit();
    }
    else if(x<=val2_)
    {
        integral_->IntegrateOpened(-1 , 1, boost::bind(&StandardNormal::FunctionToIntegral, this, _1), -x+val1_);
        return integral_->GetUpperLimit();
    }
    else
    {
        integral_->IntegrateWithSubstitution(1 , -1, boost::bind(&StandardNormal::FunctionToIntegral, this, _1), 2, -x+val2_);
        return integral_->GetUpperLimit();
    }
}

//----------------------------------------------------------------------------//

double StandardNormal::StandardNormalRandomNumber(double rnd, double average, double sigma, double xmin, double xmax, bool cutoff)
{
    double x, xl, xh;

    if(xmax<xmin)
    {
        x       =   xmin;
        xmin    =   xmax;
        xmax    =   x;
    }

    if(sigma==0)
    {
        x   =   average;
    }
    else
    {
        if(cutoff)
        {
            x   =   rnd;
        }
        else
        {
            xl  =   IntegratedProbability((xmin-average)/sigma);
            xh  =   IntegratedProbability((xmax-average)/sigma);
            x   =   xl+(xh-xl)*rnd;
        }

        x   =   average + sigma*StandardNormalRandomNumber(x);
    }

    if(x<xmin)
    {
        x   =   xmin;
    }

    if(x>xmax)
    {
        x   =   xmax;
    }

    return x;
}

//----------------------------------------------------------------------------//

double StandardNormal::FunctionToIntegral(double x)
{
    double aux  =   norm_*exp(-x*x/2);

    return aux;
}

//----------------------------------------------------------------------------//


double StandardNormal::FunctionToBuildInterpolant(double x)
{
    return IntegratedProbability(x);
}

//----------------------------------------------------------------------------//

void StandardNormal::EnableInterpolation()
{
    interpolant_    =   new Interpolant(NUM2, -5, 5, boost::bind(&StandardNormal::FunctionToBuildInterpolant, this, _1), order_of_interpolation_, true, false, false, order_of_interpolation_, true, false, false);
    do_interpolation_=true;
}

void StandardNormal::SetDoInterpolation(bool doInterpolation) {
	do_interpolation_ = doInterpolation;
}

void StandardNormal::SetIntegral(Integral* integral) {
	integral_ = integral;
}

void StandardNormal::SetInterpolant(Interpolant* interpolant) {
	interpolant_ = interpolant;
}

void StandardNormal::SetNorm(double norm) {
	norm_ = norm;
}

void StandardNormal::SetOrderOfInterpolation(int orderOfInterpolation) {
	order_of_interpolation_ = orderOfInterpolation;
}

void StandardNormal::SetVal1(double val1) {
	val1_ = val1;
}

void StandardNormal::SetVal2(double val2) {
	val2_ = val2;
}

//----------------------------------------------------------------------------//

void StandardNormal::DisableInterpolation()
{
    do_interpolation_  =   false;
}
//----------------------------------------------------------------------------//
// Setter


//----------------------------------------------------------------------------//
// Getter


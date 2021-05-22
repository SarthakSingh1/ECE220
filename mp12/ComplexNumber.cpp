#include "ComplexNumber.h"
#include "helper.h"
// Partners: Iakella2 and Ahchin2
ComplexNumber::ComplexNumber():Number(COMPLEX,0,0)
{
    number_type = COMPLEX;
    magnitude = 0.0;
    phase = 0.0;
    real_component = 0.0;
    imaginary_component = 0.0;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component):Number(COMPLEX, 0,0)
{
    number_type = COMPLEX;
    magnitude = sqrt((rval_real_component*rval_real_component)+(rval_imaginary_component*rval_imaginary_component));
    phase = calculate_phase(rval_real_component, rval_imaginary_component);
    real_component = rval_real_component;
    imaginary_component = rval_imaginary_component;
}

ComplexNumber::ComplexNumber( const ComplexNumber& other ):Number(COMPLEX, 0,0)
{
    number_type = COMPLEX;
  	magnitude = other.get_magnitude();
  	phase = other.get_phase();
    real_component = other.get_real_component() ;
  	imaginary_component = other.get_imaginary_component();
}

void ComplexNumber::set_real_component (double rval)
{
    magnitude= sqrt((rval*rval)+(imaginary_component*imaginary_component));
  	phase = calculate_phase(rval, imaginary_component);
  	real_component = rval;
}

double ComplexNumber::get_real_component() const
{
  	return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    magnitude= sqrt((real_component*real_component)+(rval*rval));
  	phase = calculate_phase(real_component, rval);
  	imaginary_component = rval;
}

double ComplexNumber::get_imaginary_component() const
{
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    return magnitude;
}

double ComplexNumber::get_phase() const{
    return phase;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    return ComplexNumber(real_component+arg.get_real_component(),imaginary_component+arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    return ComplexNumber(real_component-arg.get_real_component(), imaginary_component-arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    return ComplexNumber(real_component*arg.get_real_component()-imaginary_component*arg.get_imaginary_component(), imaginary_component*arg.get_real_component()+ real_component*arg.get_imaginary_component());
}



ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    double a = real_component ;
    double b = imaginary_component ;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    double e = ((a*c) + (b*d))/((c*c)+(d*d)) ;
    double f = ((b*c) - (a*d))/((c*c)+(d*d));
    return ComplexNumber(e,f);
}



ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
  return ComplexNumber(arg.get_real_component() + real_component, imaginary_component);
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
	return ComplexNumber(real_component-arg.get_real_component(), imaginary_component);
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
	return ComplexNumber(arg.get_real_component()*real_component, imaginary_component*arg.get_real_component());
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
	return ComplexNumber(real_component/arg.get_real_component(), imaginary_component/arg.get_real_component());
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
	return ComplexNumber(real_component, imaginary_component+arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
	return ComplexNumber(real_component, imaginary_component-arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    double a = real_component ;
    double b = imaginary_component ;
    double d = arg.get_imaginary_component();


	return ComplexNumber(-1* b*d, a*d );
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    double a = real_component ;
    double b = imaginary_component ;
    double d = arg.get_imaginary_component();
    double e = (b*d)/(d*d);
    double f = (-1* a *d)/(d*d);

	return ComplexNumber(e,f);
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}

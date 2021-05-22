#include "RealNumber.h"
#include "helper.h"
// Partners: Iakella2 and Ahchin2

RealNumber::RealNumber()
{
    number_type = REAL;
    magnitude = 0.0;
    phase = 0.0;
    real_component = 0.0 ;
}

RealNumber::RealNumber(double rval)
{
    number_type = REAL;
    magnitude = abs(rval);
    phase = calculate_phase(rval,0.0);
    real_component = rval ;
}

RealNumber::RealNumber( const RealNumber& other )
{
    number_type = REAL;
    magnitude = other.get_magnitude() ;
    phase = other.get_phase() ;
    real_component = other.get_real_component() ;
}

void RealNumber::set_real_component (double rval)
{
    magnitude = abs(rval);
    phase = calculate_phase(rval,0.0);
    real_component = rval ;
}

double RealNumber::get_real_component() const
{
    return real_component;
}

double RealNumber::get_magnitude() const{
    return magnitude;
}

double RealNumber::get_phase() const{
    return phase;
}

RealNumber RealNumber::operator + (const RealNumber& arg)
{
    return RealNumber(real_component+arg.get_real_component() );
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
    return RealNumber(real_component-arg.get_real_component() );
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
    return RealNumber(real_component*arg.get_real_component() );
}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
    
    return RealNumber(real_component/arg.get_real_component() );
}




ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){

	return ComplexNumber(real_component, arg.get_imaginary_component() );
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){

	return ComplexNumber(real_component, (-1) * arg.get_imaginary_component() );
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
    /* Your code here */
	return ImaginaryNumber(real_component * arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
    /* Your code here */
    double a = real_component ;
    double d = arg.get_imaginary_component() ;
	return ImaginaryNumber( (-1* a * d)  /(d*d));
}



ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(arg.get_real_component() + real_component, arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component - arg.get_real_component() , -1 * arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component * arg.get_real_component(), real_component * arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
    double a = real_component ;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component() ;



    return ComplexNumber(  (a*c)/((c*c)+(d*d)) , (-1 * a * d) /((c*c)+(d*d)) );
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}

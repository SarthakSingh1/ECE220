#include "ImaginaryNumber.h"
#include "helper.h"
// Partners: Iakella2 and Ahchin2

ImaginaryNumber::ImaginaryNumber():Number(IMAGINARY,  0, 0)
{
    magnitude = 0.0;
    phase = 0.0;
    imaginary_component = 0.0 ;
}

ImaginaryNumber::ImaginaryNumber(double rval):Number(IMAGINARY,  0, 0)
{
    magnitude = abs(rval);
    phase = calculate_phase(0.0,rval);
    imaginary_component = rval ;
}

ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other ):Number(IMAGINARY,  0, 0)
{
    magnitude = other.get_magnitude() ;
    phase = other.get_phase() ;
    imaginary_component = other.get_imaginary_component() ;
}

void ImaginaryNumber::set_imaginary_component (double rval)
{
    magnitude = abs(rval);
    phase = calculate_phase(0.0,rval);
    imaginary_component = rval ;
}

double ImaginaryNumber::get_imaginary_component() const
{
    return imaginary_component;
}

//Getter function for magnitude
double ImaginaryNumber::get_magnitude() const {
    return magnitude;
}

//Getter function for phase
double ImaginaryNumber::get_phase() const {
    return phase;
}

//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
{
    return ImaginaryNumber(imaginary_component+arg.get_imaginary_component());
}

ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
{
    return ImaginaryNumber(imaginary_component-arg.get_imaginary_component() );
}

RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
{
    return RealNumber(-1 * imaginary_component * arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)
{
    return RealNumber(imaginary_component / arg.get_imaginary_component());
}



ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg)
{
    return ComplexNumber(arg.get_real_component(), imaginary_component);
}

ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg)
{
    return ComplexNumber((-1)*arg.get_real_component(), imaginary_component);
}

ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg)
{
    return ImaginaryNumber(imaginary_component * arg.get_real_component());
}

ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg)
{
    return ImaginaryNumber(imaginary_component / arg.get_real_component());
}



ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
{
    return ComplexNumber( arg.get_real_component(), arg.get_imaginary_component() + imaginary_component) ;
}

ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
{
    return ComplexNumber(-1 * arg.get_real_component() , imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
{

    return ComplexNumber(-1 * arg.get_imaginary_component() * imaginary_component, imaginary_component * arg.get_real_component());

}

ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
{
    double b = imaginary_component ;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();

    return ComplexNumber(  (b*d)/((c*c)+(d*d))   , (b*c)/((c*c)+(d*d))   );
}


string ImaginaryNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << imaginary_component << 'i';
    return my_output.str();
}



 /** @file hw2.cpp
 @author Douglas Yao
 @date 1/19/2016

Converts two user-inputted numbers into binary, then performs bitwise addition and multiplication on the numbers and outputs the values. Also compares the two numbers and outputs whether one is greater than, less than, or equal to the other.

*/

#include <iostream>
#include <vector>
#include <math.h>

 /** @class Integer
 @brief Stores an integer value using bits

This class is designed to mimic the int data type

 */

class Integer {
public:

	Integer();
	Integer(unsigned int new_a);

	Integer& operator+=(const Integer& rhs);
	Integer& operator*=(const Integer& rhs);
	bool operator<(const Integer& rhs) const;
	bool operator==(const Integer& rhs) const;

	void print_as_int()  const;
	void print_as_bits() const;

private:

	std::vector<bool> bit;
	unsigned int a;
};

Integer operator+(Integer lhs, const Integer& rhs);
Integer operator*(Integer lhs, const Integer& rhs);
bool operator!=(const Integer& lhs, const Integer& rhs);
bool operator>(const Integer& lhs, const Integer& rhs);
bool operator<=(const Integer& lhs, const Integer& rhs);
bool operator>=(const Integer& lhs, const Integer& rhs);

int main() {

	unsigned int uint_value;
	std::cout << "Please input an integer a: ";
	std::cin >> uint_value;
	Integer a = uint_value; // Create Integer type with input value

	std::cout << "The base-2 represenation of a is: "; a.print_as_bits();
	std::cout << std::endl;

	std::cout << "Please input an integer b: ";
	std::cin >> uint_value;
	Integer b = uint_value; // Create Integer type with input value

	std::cout << "The base-2 represenation of b is: "; b.print_as_bits();
	std::cout << std::endl;

	// Let's do some basic arithmetic
	Integer c = a + b;
	Integer d = a*b;

	// Print out values
	std::cout << "a + b = "; c.print_as_int(); std::cout << " = "; c.print_as_bits(); std::cout << std::endl;
	std::cout << "a * b = "; d.print_as_int(); std::cout << " = "; d.print_as_bits(); std::cout << std::endl;

	// Test comparison functions
	if (a < b) std::cout << "a < b" << std::endl;
	if (a <= b) std::cout << "a <= b" << std::endl;
	if (a == b) std::cout << "a == b" << std::endl;
	if (a != b) std::cout << "a != b" << std::endl;
	if (a >= b) std::cout << "a >= b" << std::endl;
	if (a > b) std::cout << "a > b" << std::endl;

	return 0;
}



/** default constructor for Integer class

*/

Integer::Integer() {
	bit.push_back(0);
}



/** non-default constructor for Integer class. Stores inputted integer as bits in a vector of bools.

@param initial is the user-inputted integer

*/

Integer::Integer(unsigned int initial) {

	a = initial;

	// input is 0
	if (initial == 0) bit.push_back(0);

	// input is at least 1
	while (initial > 0) {
		bit.push_back(initial % 2);
		initial /= 2;
	}
}



/** performs bitwise addition between two Integers and sets the first Integer to the sum

@param rhs is the Integer to be added to the Integer that calls the function
@return the Integer that called the function with the rhs Integer added to it

*/

Integer& Integer::operator+=(const Integer& rhs) {

	// if one Integer has more bits than the other, then 0s must be added to the smaller of the two so they have the same amount of bits. Copies of both Integers are made for this reason.
	Integer copy_1 = *this;
	Integer copy_2 = rhs;

	int i = 0;
	int carry_over = 0;

	// performs bitwise addition until the smaller of the two Integer has no more bits to add
	while (i < rhs.bit.size() && i < bit.size()) {

		int new_number = rhs.bit[i] + bit[i] + carry_over;

		// if the sum of the bits and carry-over are 2 or greater
		if (new_number > 1) {
			bit[i] = (new_number - 2);
			carry_over = 1;
		}

		// if the sum is less than 2
		else {
			bit[i] = (new_number);
			carry_over = 0;
		}
		++i;
	}

	// depending on whether the right-side or left-side Integer has more bits, 0s are added to the beginning of the smaller Integer so that addition can continue

	// if the rhs Integer has more bits than the object Integer
	if (rhs.bit.size() > bit.size()) {

		while (i < rhs.bit.size()) {

			copy_1.bit.push_back(0);
			int new_number = rhs.bit[i] + copy_1.bit[i] + carry_over;

			if (new_number > 1) {
				bit.push_back(new_number - 2);
				carry_over = 1;
			}

			else {
				bit.push_back(new_number);
				carry_over = 0;
			}
			++i;
		}

		// if carry over is 1 after the final bits have been added, an additional 1 is added to the beginning of the binary value
		if (carry_over == 1)
			bit.push_back(1);
	}

	// if the rhs Integer has less bits than the object Integer
	if (rhs.bit.size() < bit.size()) {

		while (i < bit.size()) {

			copy_2.bit.push_back(0);
			int new_number = copy_2.bit[i] + bit[i] + carry_over;

			if (new_number > 1) {
				bit[i] = (new_number - 2);
				carry_over = 1;
			}

			else {
				bit[i] = (new_number);
				carry_over = 0;
			}
			++i;
		}

		if (carry_over == 1)
			bit.push_back(1);
	}

	// if the rhs Integer has the same amount of bits and the object Integer
	if (rhs.bit.size() == bit.size()) {

		if (carry_over == 1)
			bit.push_back(1);
	}

	return *this;
}



/** performs bitwise multiplication between two Integers and sets the first Integer to the product. Assumes that plus_equals is defined.

@param rhs is the Integer that the Integer that calls the function will be multiplied by
@return the Integer that called the function with the rhs Integer multiplied by it

*/

Integer& Integer::operator*=(const Integer& rhs) {

	Integer add = *this;
	Integer temp = *this;
	int n = rhs.a;

	// adds the object Integer to itself and repeats this process x times, where x is the value of the rhs Integer
	for (int i = 0; i < n - 1; ++i) {
		temp += (add);
	}

	*this = temp;
	return *this;
}



/** compares two Integers and returns true if the left hand Integer is less than the right hand Integer

@param rhs is the right hand Integer
@return true if the left hand Integer is less than the right hand Integer

*/

bool Integer::operator<(const Integer& rhs) const {

	Integer lhs = *this;

	// if the left Integer has less bits than the right Integer, it is smaller
	if (lhs.bit.size() < rhs.bit.size()) {
		return true;
	}

	// if the left Integer has more bits than the right Integer, it is not smaller
	if (lhs.bit.size() > rhs.bit.size()) {
		return false;
	}

	// if the two Integers have the same amount of bits, their bits are compared one by one, starting from the most significant bit
	if (lhs.bit.size() == rhs.bit.size()) {

		int n = lhs.bit.size();
		for (int i = 0; i < n; ++i) {

			if (lhs.bit[n - 1 - i] < rhs.bit[n - 1 - i])
				return true;

			if (lhs.bit[n - 1 - i] > rhs.bit[n - 1 - i])
				return false;

		}
	}
	return false;
}



/** compares two Integers and returns true if the two Integers are equal

@param rhs is the right hand Integer
@return true if the two Integers are equal

*/

bool Integer::operator==(const Integer& rhs) const {

	Integer lhs = *this;

	// if the two Integers have different amounts of bits, they are not equal
	if (lhs.bit.size() != rhs.bit.size())
		return false;

	// if the two Integers have the same amount of bits, their bits are compared one by one
	if (lhs.bit.size() == rhs.bit.size()) {

		int n = lhs.bit.size();
		for (int i = 0; i < n; ++i) {

			// if any two bits are not equal, then the Integers are not equal
			if (lhs.bit[i] != rhs.bit[i])
				return false;
		}
	}
	return true;
}



/** prints out the value of the Integer in bits

*/

void Integer::print_as_bits() const {

	std::cout << "(";

	for (size_t i = 0, n = bit.size(); i < n; ++i) {
		std::cout << bit[n - 1 - i]; // reverses the order of the bits, since they were added to the vector in reverse order
	}

	std::cout << ")_2";

}



/** prints out the value of the Integer as a decimal number

*/

void Integer::print_as_int() const {

	int temp = 0;

	// converts the binary value of the Integer into the decimal value
	for (int i = 0; i < bit.size(); ++i) {
		temp += bit[i] * pow(2, i);
	}

	std::cout << temp;
}



/** performs bitwise addition of two Integers and returns the sum. Assumes that += is defined.

@param lhs is the left hand Integer
@param rhs is the right hand Integer
@return the sum of the two Integers

*/

Integer operator+(Integer lhs, const Integer& rhs) {
	return lhs += rhs;
}



/** performs bitwise multiplication of two Integers and returns the product. Assumes that *= is defined.

@param lhs is the left hand Integer
@param rhs is the right hand Integer
@return the product of the two Integers

*/

Integer operator*(Integer lhs, const Integer& rhs) {
	return lhs *= rhs;
}



/** compares two Integers and returns if they are not equal. Assumes that == is defined.

@param lhs is the left hand Integer
@param rhs is the right hand Integer
@return true if the Integers are not equal

*/

bool operator!=(const Integer& lhs, const Integer& rhs) {
	return !(lhs == rhs);
}



/** compares two Integers and returns if the left hand Integer is greater than the right hand Integer. Assumes that < is defined.

@param lhs is the left hand Integer
@param rhs is the right hand Integer
@return true if the left hand Integer is greater than the right hand Integer

*/

bool operator>(const Integer& lhs, const Integer& rhs) {
	return (rhs < lhs);
}



/** compares two Integers and returns if the left hand Integer is less than or equal to the right hand Integer. Assumes that > is defined.

@param lhs is the left hand Integer
@param rhs is the right hand Integer
@return true if the left hand Integer is less than or equal to the right hand Integer

*/

bool operator<=(const Integer& lhs, const Integer& rhs) {
	return !(lhs > rhs);
}



/** compares two Integers and returns if the left hand Integer is greater than or equal to the right hand Integer. Assumes that < is defined.

@param lhs is the left hand Integer
@param rhs is the right hand Integer
@return true if the left hand Integer is greater than or equal to the right hand Integer

*/

bool operator>=(const Integer& lhs, const Integer& rhs) {
	return !(lhs < rhs);
}


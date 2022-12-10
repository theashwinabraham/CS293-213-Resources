/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#include "journey.h"

Journey::Journey(): JourneyCode(0), price(0) {}
    
Journey::Journey(unsigned int c, unsigned int p): JourneyCode(c), price(p) {}

unsigned int Journey::getJourneyCode()
{
    return JourneyCode;
}
unsigned int Journey::getPrice()
{
    return price;
}

bool Journey::operator<(Journey const &j)
{
    return JourneyCode < j.JourneyCode;
} // Usage: if (journey1 < journey2) {...}

// Journey :: istream& operator >> (istream& in, Journey &j) { /*TODO*/ } // Usage: cin >> journey1;
// Journey :: ostream& operator << (ostream& out, const Journey& j) { /*TODO*/ } // Usage: cout << journey2

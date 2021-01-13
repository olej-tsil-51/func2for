#include <iostream>                // std::cout
#include <functional>              // std::bind
#include <random>
#include <vector> 
#include <algorithm> 
using namespace std;

class Actor
{
public:
    Actor() : counter(0) {}
    void  operator()( int& i ) { 
	if (i%2) 
	{
	    i = -i;
	    counter += 1;
	}
    }
    unsigned inline changed( void ) { return counter; }
private:
    unsigned counter;
};

inline ostream& operator <<( ostream& out, const vector<int> & obj )
{ 
    out << "< "; 
    for( auto& p: obj ) 
	out << p << " "; 
    return out << ">"; 
} 

int main( int argc, char *argv[] ) 
{
    size_t limit = argc > 1 ? atol( argv[1] ) : 100;            // vectors length
    std::default_random_engine generator;                       // construct a trivial random generator engine
    std::uniform_int_distribution<int> distribution(1,100);     // https://www.cplusplus.com/reference/random/
    auto dice = std::bind ( distribution, generator );          // function for generates number in the range 1..100 
    vector<int> v0( limit ); 
    for ( auto& u: v0 ) 
	u = dice(); 
    if (limit < 50) cout << v0 << endl;
    cout << "vector full size " << v0.size() << endl;
//---------------------------------------------------------
    vector<int> v1 = v0;
    for_each ( v1.begin(), v1.end(), Actor() );
    if (limit < 50) cout << v1 << endl;
    int changed = accumulate( v1.begin(), v1.end(), 0, 
                              [](int acc, const int next)->int{ return acc + ( next < 0 ? 1 : 0 );} );
    cout << "'for_each' - was changed " << changed << " elements" << endl;
//---------------------------------------------------------
    vector<int> v2 = v0;
    Actor act2;
    for( int& i : v2 )
	act2( i );
    if (limit < 50) cout << v2 << endl;
    cout << "'for' - was changed " << act2.changed() << " elements" << endl;
//---------------------------------------------------------
    vector<int> v3 = v0;
    Actor act3;
    for ( auto i = v1.begin(); i != v1.end(); i++ )
	act3( *i );
    if (limit < 50) cout << v3 << endl;
    cout << "'for iterator' - was changed " << act3.changed() << " elements" << endl;
//---------------------------------------------------------
    vector<int> v4 = v0;
    Actor act4;
    for_each( v4.begin(), v4.end(), act4 ); 
    if (limit < 50) cout << v4 << endl;
    cout << "'functor' - was changed " << act4.changed() << " elements" << endl;
}

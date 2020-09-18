/* The CityFinder example from Thursday's lecture.
 *
 * Comments have been added to the relevant sections.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <fstream>
#include <vector>
#include <algorithm> // For set_intersection
#include <iterator>  // For back_inserter
//using namespace std;



/* Type: cityT
 * A type that stores a city's longitude, and latitude.
 */
struct cityT {
	double latitude;
	double longitude;
};




/* The number of degrees of longitude per mile, when.
 * measured at the equator.  This number is mostly
 * accurate for the US, though for polar regions in
 * Alaska might be a bit skewed.
 */
const double kDegreesPerMile = 1.0 / 69.172;





/* Straight out of the earlier lecture code. */
std::string GetLine() {
	std::string result;
	getline(std::cin, result);
	return result;
}




/* A modified version of the GetInteger function
 * that accepts positive real numbers.
 */
double GetPositiveReal() {
	while(true) {
		std::stringstream converter;
		converter << GetLine();
		
		double result;
		converter >> result;

		if(converter.fail())

			std::cout << "Please enter a real number." << std::endl;

		else {
			
            char remaining;
			converter >> remaining;
			
			if(converter.fail()) {
				if(result > 0.0)
					return result;
				else
					std::cout << "Please enter a positive real number." << std::endl;
			}
			else
				std::cout << "Unexpected character: " << remaining << std::endl;

		}
		
		std::cout << "Retry: ";
	}
}




/* Loads the place-data.txt file from disk and populates a
 * map<string, cityT> with the information.
 */
void LoadData(std::map<std::string, cityT>& cityLookup) {

	std::ifstream input("place-data.txt");
	std::string data, name;


	/* This uses a bit of shorthand that reads in the line and then
	 * continues looping while the input stream isn't in a fail state.
	 * In general, you can test if(myStream) as shorthand for
	 * if(!myStream.fail());
	 */
	while(getline(input, name)) {


		/* Assuming data is well-formatted, read in the line
		 * with the longitude and latitude data and run it
		 * through a stringstream.
		 */
		getline(input, data);
		std::stringstream converter(data);


		/* Load the information into the cityT struct.
		 * We'll assume the file is well-formed.
		 */
		cityT city;
		converter >> city.latitude;
		converter >> city.longitude;

		/* Insert the key-value pair "name: city" into the map. */
		cityLookup.insert(make_pair(name, city));
	}

	/* Print some useful information out. */
	std::cout << "Data exists for ";
	std::cout << cityLookup.size() << " cities." << std::endl;
}




/* Useful typedefs to simplify the code we'll be writing.
 * The code is much longer without these!
 */
typedef std::multimap<double, std::string> CoordMap;






/* Given a map from strings to cityTs, construct two
 * multimaps mapping from doubles to cityTs that correspond
 * to the longitude and latitudes of the cities.
 */
void PopulateLookupTables(std::map< std::string, cityT>&  cityLookup,    CoordMap& longLookup,     CoordMap& latLookup)
{
	for(std::map<std::string, cityT>::iterator itr = cityLookup.begin(); itr != cityLookup.end(); ++itr)
	{
		/* Key should be longitude (latitude) of the
		 * element being iterated over with value
		 * equal to the city name.
		 */
		longLookup.insert(make_pair(itr->second.longitude, itr->first));

		latLookup.insert(make_pair( itr->second.latitude,  itr->first));
	}
}





/* Runs the algorithm described in class to locate cities
 * near the center city.
 */
void FindNearbyCities(std::map<std::string, cityT>& cityLookup,    CoordMap& longLookup,     CoordMap& latLookup,  double radius,  cityT center)
{


	/* Find cities with nearby longitudes.  Note that if
	 * we wanted to performance-tune this code we would
	 * pull the code for computing upper_bound out of the
	 * loop to avoid recomputing it.
	 */
	std::set<std::string> nearbyLongs;
	for(CoordMap::iterator itr = longLookup.lower_bound(center.longitude - radius);
		itr != longLookup.upper_bound(center.longitude + radius); ++itr)
		nearbyLongs.insert(itr->second);



	/* Repeat the above for latitude. */
	std::set<std::string> nearbyLats;
	for(CoordMap::iterator itr = latLookup.lower_bound(center.latitude - radius);
		itr != latLookup.upper_bound(center.latitude + radius); ++itr)
		nearbyLats.insert(itr->second);



	/* Using the set_intersection algorithm, compute the
	 * intersection of these sets.  We'll discuss algorithms
	 * more next week.
	 */
	std::vector<std::string> candidates;
	set_intersection(nearbyLongs.begin(), nearbyLongs.end(),
					 nearbyLats.begin(), nearbyLats.end(),
					 back_inserter(candidates));



	/* 
        Finally, iterate over the intersection and see what
	    cities are in range.
	*/
	for(size_t i = 0; i < candidates.size(); ++i) {

		cityT city = cityLookup[candidates[i]];

		double dx = city.longitude - center.longitude;
		double dy = city.latitude  - center.latitude;

		if(dx * dx + dy * dy <= radius * radius)
			std::cout << candidates[i] << std::endl;
	}
}








int main() {
	/* The city lookup tables. */
	std::map<std::string, cityT> cityLookup;


	CoordMap longLookup;
	CoordMap latLookup;
	



	/* Fill our tables with some info. */
	LoadData(cityLookup);


    /* Populate independent tablets with longitud|city  and latitud|city */
	PopulateLookupTables(cityLookup, longLookup, latLookup);



	while(true) {
		/* Prompt the user for a city name. */
		std::cout << "Please enter a city: ";
		std::string city = GetLine();


		/* If the user just hit enter, we're done. */
		if(city.empty())
			break;


		/* Look up the city, print data if found. */
		std::map<std::string, cityT>::iterator itr =  cityLookup.find(city);


		/* If the city exists, ask the user for more information. */
		if(itr != cityLookup.end()) {

			std::cout << "Enter radius: ";
			double radius = GetPositiveReal() * kDegreesPerMile;

			FindNearbyCities(cityLookup, longLookup, latLookup, radius, itr->second);
		}
		else
			std::cout << "City not found." << std::endl;
	}

	return 0;
}
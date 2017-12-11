#define textLookUpTableLen 39

//Array for the text sprites in ASCII

const unsigned short textLookUpTable[64] __attribute__((aligned(4))) =
{
	//Acending numbers
	48,49,50,51,52,
	53,54,55,56,57,
	//Acending letter
	65,66,67,68,69,
	70,71,72,73,74,
	75,76,77,78,79,
	80,81,82,83,84,
	85,86,87,88,89,90,
	//copy right symbol using @
	64,
	//- ,* and !
	45, 120,33,
	//Padding 24 extra
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,
};

//{{BLOCK(mario)

//======================================================================
//
//	mario, 8x192@4, 
//	+ palette 16 entries, not compressed
//	+ 24 tiles not compressed
//	Total size: 32 + 768 = 800
//
//	Time-stamp: 2017-12-09, 23:46:03
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned short marioTiles[384] __attribute__((aligned(4)))=
{
	0x0000,0x1110,0x0000,0x1111,0x0000,0x2333,0x3000,0x2232,
	0x3000,0x2332,0x3000,0x2223,0x0000,0x2220,0x0000,0x3133,
	0x0011,0x0000,0x1111,0x0001,0x0232,0x0000,0x2232,0x0002,
	0x2322,0x0022,0x3332,0x0003,0x2222,0x0000,0x0033,0x0000,
	0x3000,0x3133,0x3000,0x1133,0x2000,0x1213,0x2000,0x1112,
	0x2000,0x1111,0x0000,0x0111,0x3000,0x0033,0x3000,0x0033,
	0x3313,0x0003,0x3311,0x0033,0x3121,0x0022,0x2111,0x0022,
	0x1111,0x0022,0x1110,0x0000,0x3300,0x0003,0x3300,0x0033,

	0x0000,0x0000,0x0000,0x1110,0x0000,0x1111,0x0000,0x2333,
	0x3000,0x2232,0x3000,0x2332,0x3000,0x2223,0x0000,0x2220,
	0x0000,0x0000,0x0011,0x0000,0x1111,0x0001,0x0232,0x0000,
	0x2232,0x0002,0x2322,0x0022,0x3332,0x0003,0x2222,0x0000,
	0x0000,0x3333,0x2000,0x3333,0x2200,0x3331,0x3300,0x1111,
	0x1300,0x1111,0x1330,0x1011,0x0030,0x3300,0x0000,0x3300,
	0x2031,0x0000,0x2233,0x0002,0x2233,0x0000,0x0111,0x0000,
	0x0111,0x0000,0x0011,0x0000,0x0003,0x0000,0x0033,0x0000,

	0x0000,0x1110,0x0000,0x1111,0x0000,0x2333,0x3000,0x2232,
	0x3000,0x2332,0x3000,0x2223,0x0000,0x2220,0x0000,0x3133,
	0x0011,0x0000,0x1111,0x0001,0x0232,0x0000,0x2232,0x0002,
	0x2322,0x0022,0x3332,0x0003,0x2222,0x0000,0x0033,0x0000,
	0x3000,0x1333,0x3000,0x1133,0x3000,0x1333,0x1000,0x2233,
	0x0000,0x2231,0x0000,0x1110,0x0000,0x3330,0x0000,0x3330,
	0x0331,0x0000,0x2112,0x0000,0x1111,0x0000,0x1112,0x0000,
	0x0111,0x0000,0x0333,0x0000,0x3333,0x0000,0x0003,0x0000,

	0x0000,0x1110,0x0000,0x1111,0x0000,0x2333,0x3000,0x2232,
	0x3000,0x2332,0x3000,0x2223,0x0000,0x2220,0x3300,0x1133,
	0x0011,0x0000,0x1111,0x0001,0x0232,0x0000,0x2232,0x0002,
	0x2322,0x0022,0x3332,0x0003,0x2222,0x0000,0x0033,0x0000,
	0x3322,0x1133,0x0222,0x2133,0x0022,0x1111,0x1000,0x1111,
	0x1100,0x1111,0x1330,0x0011,0x3330,0x0000,0x3300,0x0003,
	0x3331,0x0222,0x3111,0x0223,0x0111,0x0030,0x1111,0x0033,
	0x1111,0x0033,0x1110,0x0033,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x1100,0x0000,0x1110,0x0000,0x3330,
	0x0000,0x2323,0x0000,0x3323,0x0000,0x2233,0x0000,0x2200,
	0x0000,0x2220,0x0111,0x2220,0x1111,0x2211,0x2322,0x3330,
	0x2322,0x3332,0x3222,0x3222,0x3322,0x0333,0x2222,0x0032,
	0x3300,0x1333,0x3330,0x3333,0x3322,0x3333,0x0222,0x1311,
	0x3020,0x1111,0x3300,0x1113,0x3330,0x1111,0x0030,0x1111,
	0x1333,0x0003,0x3331,0x3001,0x1111,0x3001,0x1121,0x3312,
	0x1111,0x3311,0x1111,0x3311,0x0111,0x0000,0x0000,0x0000,

	0x0000,0x1100,0x2000,0x1110,0x2220,0x2323,0x3220,0x2323,
	0x3220,0x2233,0x3000,0x2333,0x0000,0x3323,0x0000,0x2223,
	0x0011,0x0000,0x0111,0x0002,0x3232,0x0222,0x3232,0x0223,
	0x3322,0x0223,0x3332,0x0003,0x3233,0x0000,0x3222,0x0000,
	0x1000,0x2211,0x3300,0x3311,0x3300,0x3113,0x3300,0x1213,
	0x3300,0x1113,0x3000,0x1113,0x0000,0x0000,0x0000,0x0000,
	0x1122,0x0001,0x1133,0x0033,0x3113,0x0033,0x3121,0x0033,
	0x3111,0x0033,0x3111,0x0003,0x0000,0x0000,0x0000,0x0000,
};

const unsigned short marioPal[16] __attribute__((aligned(4)))=
{
	0x7C1F,0x10D6,0x127C,0x01AD,0x781F,0x7BFE,0x02C0,0x127C,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};
const unsigned short luigiPal[16] __attribute__((aligned(4))) =
{
	0x781F,0x7BFE,0x127C,0x02C0,0x7C1F,0x10D6,0x127C,0x01AD,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};
//}}BLOCK(mario)

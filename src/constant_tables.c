#ifndef _CHARACTER_CAPACITY_TABLE_H_
#define _CHARACTER_CAPACITY_TABLE_H_

#include <qr_utils.h>

qr_version_properties g_character_capacity_table[QR_VERSION_MAX] =
{
    [QR_VERSION_1] =    {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                41,	                25, 	                17,         	10,
                                34,	                20, 	                14,         	8,
                                27,	                16, 	                11,         	7,
                                17,	                10, 	                7,              4,
                            },
                        },
    [QR_VERSION_2] =    {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                77,	                47,	                    32,	            20,
                                63,	                38,	                    26,	            16,
                                48,	                29,	                    20,	            12,
                                34,	                20,	                    14,	            8,
                            },
                        },
    [QR_VERSION_3] =    {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                127,            	77,                 	53,         	32,
                                101,            	61,                 	42,         	26,
                                77,              	47,                 	32,         	20,
                                58,              	35,                 	24,         	15,
                            },
                        },
    [QR_VERSION_4] =    {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                187	,               114,                	78,         	48,
                                149,                90,                  	62,         	38,
                                111,                67,                  	46,         	28,
                                82,             	50,                  	34,         	21,
                            },
                        },
    [QR_VERSION_5] =    {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                255,	            154,                    106,          	65,
                                202,                122,                    84,             52,
                                144,	            87,	                    60,	            37,
                                106,	            64,	                    44,	            27,
                            },
                        },
    [QR_VERSION_6] =    {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                322,            	195,                	134,        	82,
                                255,            	154,                	106,        	65,
                                178,            	108,                	74,     	    45,
                                139,            	84	,                   58,     	    36,
                            },
                        },
    [QR_VERSION_7] =    {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                370,            	224,                	154,        	95,
                                293,            	178,                	122,        	75,
                                207,            	125,                	86,     	    53,
                                154,            	93	,                   64,     	    39,
                            },
                        },
    [QR_VERSION_8] =    {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                461,            	279,                	192,            118,
                                365,            	221,                	152,            93,
                                259,            	157,                	108,            66,
                                202,            	122,                	84,             52,
                            },
                        },
    [QR_VERSION_9] =    {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                552,            	335,                	230,            141,
                                432,            	262,                	180,            111,
                                312,            	189,                	130,            80,
                                235,            	143,                	98,             60,
                            },
                        },
    [QR_VERSION_10] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                652,            	395,	                271,	        167,
                                513,            	311,	                213,	        131,
                                364,            	221,	                151,	        93,
                                288,            	174,	                119,	        74,
                            },
                        },
    [QR_VERSION_11] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                772,	            468,	                321,	        198,
                                604,	            366,	                251,	        155,
                                427,	            259,	                177,	        109,
                                331,	            200,	                137,	        85,
                            },
                        },
    [QR_VERSION_12] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                883,	            535,    	            367,	        226,
                                691,	            419,    	            287,	        177,
                                489,	            296,    	            203,	        125,
                                374,	            227,    	            155,	        96,
                            },
                        },
    [QR_VERSION_13] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                1022,               619,                    425,         	262,
                                796,                483,                    331,            204,
                                580,                352,                    241,            149,
                                427,                259,                    177,            109,
                            },
                        },
    [QR_VERSION_14] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                1101,               667,                	458,	        282,
                                871,                528,                	362,	        223,
                                621,                376,                	258,	        159,
                                468,                283,                	194,	        120,
                            },
                        },
    [QR_VERSION_15] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                1250,	            758,	                520,        	320,
                                991,	            600,	                412,        	254,
                                703,	            426,	                292,        	180,
                                530,	            321,	                220,        	136,
                            },
                        },
    [QR_VERSION_16] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                1408,	            854,	                586,	        361,
                                1082,	            656,	                450,	        277,
                                775,                470,	                322,	        198,
                                602,                365,	                250,	        154,
                            },
                        },
    [QR_VERSION_17] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                1548,	            938,	                644,	        397,
                                1212,	            734,	                504,	        310,
                                876,                531,	                364,	        224,
                                674,                408,	                280,	        173,
                            },
                        },
    [QR_VERSION_18] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                1725,               1046,	                718,	        442,
                                1346,           	816,	                560,	        345,
                                948,            	574,	                394,	        243,
                                746,            	452,	                310,	        191,
                            },
                        },
    [QR_VERSION_19] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                1903,               1153,               	792,        	488,
                                1500,	            909,	                624,	        384,
                                1063,	            644,	                442,	        272,
                                813,	            493,	                338,	        208,
                            },
                        },
    [QR_VERSION_20] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                2061,               1249,               	858,        	528,
                                1600,	            970,	                666,	        410,
                                1159,	            702,	                482,	        297,
                                919,	            557,	                382,	        235,
                            },
                        },
    [QR_VERSION_21] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                2232,               1352,               	929,        	572,
                                1708,               1035,               	711,        	438,
                                1224,	            742,	                509,	        314,
                                969,	            587,	                403,	        248,
                            },
                        },
    [QR_VERSION_22] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                2409,	            1460,                   1003,	        618,
                                1872,	            1134,               	779,	        480,
                                1358,	            823,	                565,	        348,
                                1056,	            640,	                439,	        270,
                            },
                        },
    [QR_VERSION_23] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                2620,           	1588,                   1091,	        672,
                                2059,           	1248,                   857,	        528,
                                1468,           	890,                    611,	        376,
                                1108,           	672,                    461,	        284,
                            },
                        },
    [QR_VERSION_24] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                2812,           	1704,                   1171,        	721,
                                2188,           	1326,                   911,        	561,
                                1588,           	963,                    661,        	407,
                                1228,           	744,                    511,        	315,
                            },
                        },
    [QR_VERSION_25] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                3057,	            1853,                   1273,	        784,
                                2395,	            1451,                   997,	        614,
                                1718,	            1041,                   715,	        440,
                                1286,	            779,                    535,	        330,
                            },
                        },
    [QR_VERSION_26] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                3283,           	1990,	                1367,	        842,
                                2544,           	1542,	                1059,	        652,
                                1804,           	1094,	                751,	        462,
                                1425,           	864,                    593,	        365,
                            },
                        },
    [QR_VERSION_27] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                3517,	            2132,                   1465,	        902,
                                2701,	            1637,                   1125,	        692,
                                1933,	            1172,                   805,	        496,
                                1501,	            910,                    625,	        385,
                            },
                        },
    [QR_VERSION_28] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                3669,           	2223,               	1528,	        940,
                                2857,           	1732,               	1190,	        732,
                                2085,           	1263,               	868,	        534,
                                1581,           	958,                    658,	        405,
                            },
                        },
    [QR_VERSION_29] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                3909,           	2369,               	1628,           1002,
                                3035,           	1839,               	1264,           778,
                                2181,           	1322,               	908,            559,
                                1677,           	1016,               	698,            430,
                            },
                        },
    [QR_VERSION_30] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                4158,             	2520,               	1732,           1066,
                                3289,             	1994,               	1370,           843,
                                2358,             	1429,               	982,            604,
                                1782,             	1080,               	742,            457,
                            },
                        },
    [QR_VERSION_31] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                4417,           	2677,	                1840,	        1132,
                                3486,           	2113,	                1452,	        894,
                                2473,           	1499,	                1030,	        634,
                                1897,           	1150,	                790,            486,
                            },
                        },
    [QR_VERSION_32] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                4686,           	2840,               	1952,           1201,
                                3693,           	2238,               	1538,           947,
                                2670,           	1618,               	1112,           684,
                                2022,           	1226,               	842,            518,
                            },
                        },
    [QR_VERSION_33] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                4965,	            3009,   	            2068,       	1273,
                                3909,	            2369,   	            1628,       	1002,
                                2805,	            1700,   	            1168,       	719,
                                2157,	            1307,   	            898,	        553,
                            },
                        },
    [QR_VERSION_34] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                5253,           	3183,               	2188,       	1347,
                                4134,           	2506,               	1722,       	1060,
                                2949,           	1787,               	1228,       	756,
                                2301,           	1394,               	958,        	590,
                            },
                        },
    [QR_VERSION_35] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                5529,	            3351,	                2303,	        1417,
                                4343,	            2632,	                1809,	        1113,
                                3081,	            1867,	                1283,	        790,
                                2361,	            1431,	                983,            605,
                            },
                        },
    [QR_VERSION_36] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                5836,	            3537,	                2431,	        1496,
                                4588,	            2780,	                1911,	        1176,
                                3244,	            1966,	                1351,	        832,
                                2524,	            1530,	                1051,	        647,
                            },
                        },
    [QR_VERSION_37] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                6153,	            3729,	                2563,	        1577,
                                4775,	            2894,	                1989,	        1224,
                                3417,	            2071,	                1423,	        876,
                                2625,	            1591,	                1093,	        673,
                            },
                        },
    [QR_VERSION_38] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                6479,           	3927,               	2699,	        1661,
                                5039,           	3054,               	2099,	        1292,
                                3599,           	2181,               	1499,	        923,
                                2735,           	1658,               	1139,	        701,
                            },
                        },
    [QR_VERSION_39] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                6743,	            4087,	                2809,	        1729,
                                5313,	            3220,	                2213,	        1362,
                                3791,	            2298,	                1579,	        972,
                                2927,	            1774,	                1219,	        750,
                            },
                        },
    [QR_VERSION_40] =   {
                            {   // numeric mode     // alphanumeric mode    // byte mode    // kanji mode
                                7089,           	4296,	                2953,	        1817,
                                5596,           	3391,	                2331,	        1435,
                                3993,           	2420,	                1663,	        1024,
                                3057,           	1852,	                1273,	        784,
                            },
                        }
};

qr_ec_version_entry g_ec_table[QR_VERSION_MAX] = 
{
    [QR_VERSION_1] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 19,
                .ec_codewords_per_block = 7,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 19,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 16,
                .ec_codewords_per_block = 10,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 16,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 13,
                .ec_codewords_per_block = 13,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 13,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 9,
                .ec_codewords_per_block = 17,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 9,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
        },
    },
    [QR_VERSION_2] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 34,
                .ec_codewords_per_block = 10,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 34,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 28,
                .ec_codewords_per_block = 16,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 28,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 22,
                .ec_codewords_per_block = 22,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 22,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 16,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 16,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
        },
    },
    [QR_VERSION_3] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 55,
                .ec_codewords_per_block = 15,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 55,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 44,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 44,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 34,
                .ec_codewords_per_block = 18,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 17,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 26,
                .ec_codewords_per_block = 22,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 13,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
        },
    },
    [QR_VERSION_4] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 80,
                .ec_codewords_per_block = 20,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 80,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 64,
                .ec_codewords_per_block = 18,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 32,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 48,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 36,
                .ec_codewords_per_block = 16,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 9,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
        },
    },
    [QR_VERSION_5] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 108,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 108,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 86,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 43,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 62,
                .ec_codewords_per_block = 18,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 16,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 46,
                .ec_codewords_per_block = 22,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 11,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 12,
                    },
                },
            },
        },
    },
    [QR_VERSION_6] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 136,
                .ec_codewords_per_block = 18,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 68,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 108,
                .ec_codewords_per_block = 16,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 27,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 76,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 19,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 60,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
        },
    },
    [QR_VERSION_7] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 156,
                .ec_codewords_per_block = 20,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 78,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 124,
                .ec_codewords_per_block = 18,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 31,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 88,
                .ec_codewords_per_block = 18,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 14,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 15,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 66,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 13,
                    },
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 14,
                    },
                },
            },
        },
    },
    [QR_VERSION_8] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 194,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 97,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 154,
                .ec_codewords_per_block = 22,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 38,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 39,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 110,
                .ec_codewords_per_block = 22,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 18,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 19,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 86,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 14,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 15,
                    },
                },
            },
        },
    },
    [QR_VERSION_9] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 232,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 116,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 182,
                .ec_codewords_per_block = 22,
                .groups =
                {
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 36,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 37,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 132,
                .ec_codewords_per_block = 20,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 16,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 17,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 100,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 12,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 13,
                    },
                },
            },
        },
    },
    [QR_VERSION_10] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 274,
                .ec_codewords_per_block = 18,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 68,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 69,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 216,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 43,
                    },
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 44,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 154,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 19,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 20,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 122,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_11] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 324,
                .ec_codewords_per_block = 20,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 81,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 254,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 50,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 51,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 180,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 22,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 23,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 140,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 12,
                    },
                    {
                        .block_count            = 8,
                        .codewords_per_block    = 13,
                    },
                },
            },
        },
    },
    [QR_VERSION_12] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 370,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 92,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 93,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 290,
                .ec_codewords_per_block = 22,
                .groups =
                {
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 36,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 37,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 206,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 20,
                    },
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 21,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 158,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 14,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 15,
                    },
                },
            },
        },
    },
    [QR_VERSION_13] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 428,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 107,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 334,
                .ec_codewords_per_block = 22,
                .groups =
                {
                    {
                        .block_count            = 8,
                        .codewords_per_block    = 37,
                    },
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 38,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 244,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 8,
                        .codewords_per_block    = 20,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 21,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 180,
                .ec_codewords_per_block = 22,
                .groups =
                {
                    {
                        .block_count            = 12,
                        .codewords_per_block    = 11,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 12,
                    },
                },
            },
        },
    },
    [QR_VERSION_14] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 461,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 115,
                    },
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 116,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 365,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 40,
                    },
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 41,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 261,
                .ec_codewords_per_block = 20,
                .groups =
                {
                    {
                        .block_count            = 11,
                        .codewords_per_block    = 16,
                    },
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 17,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 197,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 11,
                        .codewords_per_block    = 12,
                    },
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 13,
                    },
                },
            },
        },
    },
    [QR_VERSION_15] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 523,
                .ec_codewords_per_block = 22,
                .groups =
                {
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 87,
                    },
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 88,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 415,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 41,
                    },
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 42,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 295,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 223,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 11,
                        .codewords_per_block    = 12,
                    },
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 13,
                    },
                },
            },
        },
    },
    [QR_VERSION_16] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 589,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 98,
                    },
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 99,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 453,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 45,
                    },
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 46,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 325,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 15,
                        .codewords_per_block    = 19,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 20,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 253,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 13,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_17] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 647,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 107,
                    },
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 108,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 507,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 10,
                        .codewords_per_block    = 46,
                    },
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 47,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 367,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 22,
                    },
                    {
                        .block_count            = 15,
                        .codewords_per_block    = 23,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 283,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 14,
                    },
                    {
                        .block_count            = 17,
                        .codewords_per_block    = 15,
                    },
                },
            },
        },
    },
    [QR_VERSION_18] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 721,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 120,
                    },
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 121,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 563,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 9,
                        .codewords_per_block    = 43,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 44,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 397,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 17,
                        .codewords_per_block    = 22,
                    },
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 23,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 313,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 14,
                    },
                    {
                        .block_count            = 19,
                        .codewords_per_block    = 15,
                    },
                },
            },
        },
    },
    [QR_VERSION_19] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 795,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 113,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 114,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 627,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 44,
                    },
                    {
                        .block_count            = 11,
                        .codewords_per_block    = 45,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 445,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 17,
                        .codewords_per_block    = 21,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 22,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 341,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 9,
                        .codewords_per_block    = 13,
                    },
                    {
                        .block_count            = 16,
                        .codewords_per_block    = 14,
                    },
                },
            },
        },
    },
    [QR_VERSION_20] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 861,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 107,
                    },
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 108,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 669,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 41,
                    },
                    {
                        .block_count            = 13,
                        .codewords_per_block    = 42,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 485,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 15,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 385,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 15,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 10,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_21] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 932,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 116,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 117,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 714,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 17,
                        .codewords_per_block    = 42,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 512,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 17,
                        .codewords_per_block    = 22,
                    },
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 23,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 406,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 19,
                        .codewords_per_block    = 16,
                    },
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 17,
                    },
                },
            },
        },
    },
    [QR_VERSION_22] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 1006,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 111,
                    },
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 112,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 782,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 17,
                        .codewords_per_block    = 46,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 568,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 16,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 442,
                .ec_codewords_per_block = 24,
                .groups =
                {
                    {
                        .block_count            = 34,
                        .codewords_per_block    = 13,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
        },
    },
    [QR_VERSION_23] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 1094,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 121,
                    },
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 122,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 860,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 47,
                    },
                    {
                        .block_count            = 14,
                        .codewords_per_block    = 48,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 614,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 11,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 14,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 464,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 16,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 14,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_24] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 1174,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 117,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 118,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 914,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 45,
                    },
                    {
                        .block_count            = 14,
                        .codewords_per_block    = 46,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 664,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 11,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 16,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 514,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 30,
                        .codewords_per_block    = 16,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 17,
                    },
                },
            },
        },
    },
    [QR_VERSION_25] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 1276,
                .ec_codewords_per_block = 26,
                .groups =
                {
                    {
                        .block_count            = 8,
                        .codewords_per_block    = 106,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 107,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1000,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 8,
                        .codewords_per_block    = 47,
                    },
                    {
                        .block_count            = 13,
                        .codewords_per_block    = 48,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 718,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 22,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 538,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 22,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 13,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_26] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 1370,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 10,
                        .codewords_per_block    = 114,
                    },
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 115,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1062,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 19,
                        .codewords_per_block    = 46,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 47,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 754,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 28,
                        .codewords_per_block    = 22,
                    },
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 23,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 596,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 33,
                        .codewords_per_block    = 16,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 17,
                    },
                },
            },
        },
    },
    [QR_VERSION_27] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 1468,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 8,
                        .codewords_per_block    = 122,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 123,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1128,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 22,
                        .codewords_per_block    = 45,
                    },
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 46,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 808,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 8,
                        .codewords_per_block    = 23,
                    },
                    {
                        .block_count            = 26,
                        .codewords_per_block    = 24,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 628,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 12,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 28,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_28] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 1531,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 117,
                    },
                    {
                        .block_count            = 10,
                        .codewords_per_block    = 118,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1193,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 45,
                    },
                    {
                        .block_count            = 23,
                        .codewords_per_block    = 46,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 871,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 31,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 661,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 11,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 31,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_29] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 1631,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 116,
                    },
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 117,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1267,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 21,
                        .codewords_per_block    = 45,
                    },
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 46,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 911,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 23,
                    },
                    {
                        .block_count            = 37,
                        .codewords_per_block    = 24,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 701,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 19,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 26,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_30] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 1735,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 5,
                        .codewords_per_block    = 115,
                    },
                    {
                        .block_count            = 10,
                        .codewords_per_block    = 116,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1373,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 19,
                        .codewords_per_block    = 47,
                    },
                    {
                        .block_count            = 10,
                        .codewords_per_block    = 48,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 985,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 15,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 25,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 745,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 23,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 25,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_31] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 1843,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 13,
                        .codewords_per_block    = 115,
                    },
                    {
                        .block_count            = 3,
                        .codewords_per_block    = 116,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1455,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 46,
                    },
                    {
                        .block_count            = 29,
                        .codewords_per_block    = 47,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 1033,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 42,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 793,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 23,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 28,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_32] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 1955,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 17,
                        .codewords_per_block    = 115,
                    },
                    {
                        .block_count            = 0,
                        .codewords_per_block    = 0,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1541,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 10,
                        .codewords_per_block    = 46,
                    },
                    {
                        .block_count            = 23,
                        .codewords_per_block    = 47,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 1115,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 10,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 35,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 845,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 19,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 35,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_33] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 2071,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 17,
                        .codewords_per_block    = 115,
                    },
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 116,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1631,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 14,
                        .codewords_per_block    = 46,
                    },
                    {
                        .block_count            = 21,
                        .codewords_per_block    = 47,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 1171,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 29,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 19,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 901,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 11,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 46,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_34] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 2191,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 13,
                        .codewords_per_block    = 115,
                    },
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 116,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1725,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 14,
                        .codewords_per_block    = 46,
                    },
                    {
                        .block_count            = 23,
                        .codewords_per_block    = 47,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 1231,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 44,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 961,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 59,
                        .codewords_per_block    = 16,
                    },
                    {
                        .block_count            = 1,
                        .codewords_per_block    = 17,
                    },
                },
            },
        },
    },
    [QR_VERSION_35] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 2306,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 12,
                        .codewords_per_block    = 121,
                    },
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 122,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1812,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 12,
                        .codewords_per_block    = 47,
                    },
                    {
                        .block_count            = 26,
                        .codewords_per_block    = 48,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 1286,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 39,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 14,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 986,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 22,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 41,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_36] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 2434,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 121,
                    },
                    {
                        .block_count            = 14,
                        .codewords_per_block    = 122,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1914,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 47,
                    },
                    {
                        .block_count            = 34,
                        .codewords_per_block    = 48,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 1354,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 46,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 10,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 1054,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 2,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 64,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_37] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 2566,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 17,
                        .codewords_per_block    = 122,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 123,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 1992,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 29,
                        .codewords_per_block    = 46,
                    },
                    {
                        .block_count            = 14,
                        .codewords_per_block    = 47,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 1426,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 49,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 10,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 1096,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 24,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 46,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_38] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 2702,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 122,
                    },
                    {
                        .block_count            = 18,
                        .codewords_per_block    = 123,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 2102,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 13,
                        .codewords_per_block    = 46,
                    },
                    {
                        .block_count            = 32,
                        .codewords_per_block    = 47,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 1502,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 48,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 14,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 1142,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 42,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 32,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_39] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 2812,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 20,
                        .codewords_per_block    = 117,
                    },
                    {
                        .block_count            = 4,
                        .codewords_per_block    = 118,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 2216,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 40,
                        .codewords_per_block    = 47,
                    },
                    {
                        .block_count            = 7,
                        .codewords_per_block    = 48,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 1582,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 43,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 22,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 1222,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 10,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 67,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
    [QR_VERSION_40] =
    {
        .correction_levels =
        {
            [QR_CORRECTION_LEVEL_L] =
            {
                .total_codewords_count  = 2956,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 19,
                        .codewords_per_block    = 118,
                    },
                    {
                        .block_count            = 6,
                        .codewords_per_block    = 119,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_M] =
            {
                .total_codewords_count  = 2334,
                .ec_codewords_per_block = 28,
                .groups =
                {
                    {
                        .block_count            = 18,
                        .codewords_per_block    = 47,
                    },
                    {
                        .block_count            = 31,
                        .codewords_per_block    = 48,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_Q] =
            {
                .total_codewords_count  = 1666,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 34,
                        .codewords_per_block    = 24,
                    },
                    {
                        .block_count            = 34,
                        .codewords_per_block    = 25,
                    },
                },
            },
            [QR_CORRECTION_LEVEL_H] =
            {
                .total_codewords_count  = 1276,
                .ec_codewords_per_block = 30,
                .groups =
                {
                    {
                        .block_count            = 20,
                        .codewords_per_block    = 15,
                    },
                    {
                        .block_count            = 61,
                        .codewords_per_block    = 16,
                    },
                },
            },
        },
    },
};


#endif
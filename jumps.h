#include "../../inc/types.h"
#include "vectors.h"

#include <list>

typedef struct
{
	Vector3 start;
	Vector3 end;
	float width;
} RotatableCuboid;

struct StuntJump {
	RotatableCuboid jump;
	RotatableCuboid landing;
};

std::list<StuntJump> stunts = {};

// Shims so that we can just paste the (processed) decompiled game script into this and extract the jump data

RotatableCuboid processAxisAlignedBB(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float centreX = (x1 + x2) / 2.f;
	float width = abs(x1 - x2);
	
	return {
		v3(centreX, min(y1, y2), min(z1, z2)),
		v3(centreX, max(y1, y2), max(z1, z2)),
		width
	};
}

namespace JUMPS_MISC { // So we don't conflict with the ScriptHook natives, but it's easy to find and replace 'MISC::' with 'JUMPS_MISC::'
	void ADD_STUNT_JUMP(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, float camX, float camY, float camZ, int unk1, int unk2 = 0, int unk3 = 0)
	{
		RotatableCuboid jump = processAxisAlignedBB(x1, y1, z1, x2, y2, z2);
		RotatableCuboid landing = processAxisAlignedBB(x3, y3, z3, x4, y4, z4);

		stunts.push_back({
			jump,
			landing
		});
	}

	void ADD_STUNT_JUMP_ANGLED(float x1, float y1, float z1, float x2, float y2, float z2, float radius1, float x3, float y3, float z3, float x4, float y4, float z4, float radius2, float camX, float camY, float camZ, int unk1, int unk2, int unk3)
	{
		RotatableCuboid jump = {
			v3(x1, y1, z1),
			v3(x2, y2, z2),
			radius1
		};

		RotatableCuboid landing = {
			v3(x3, y3, z3),
			v3(x4, y4, z4),
			radius2
		};

		stunts.push_back({
			jump,
			landing
		});
	}
}

// Decompiled game script:

Vector3 func_75(Vector3 vParam0, bool bParam1)
{
	Vector3 vVar0;

	vVar0 = v3(-15.f, -15.f, -2.f);
	if (bParam1)
	{
		vVar0 = v3(15.f, 15.f, 5.f);
	}
	vVar0 = v3(vParam0.x + vVar0.x, vParam0.y + vVar0.y, vParam0.z + vVar0.z);
	return vVar0;
}

Vector3 func_76(Vector3 vParam0, bool bParam1)
{
	Vector3 vVar0;

	vVar0 = v3(-5.f, -5.f, 0.f);
	if (bParam1)
	{
		vVar0 = v3(5.f, 5.f, 3.f);
	}
	vVar0 = v3(vParam0.x + vVar0.x, vParam0.y + vVar0.y, vParam0.z + vVar0.z);
	return vVar0;
}

void initializeJumps() {
	stunts.clear();

	Vector3 vVar0;
	Vector3 vVar1;
	Vector3 vVar2;

	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(2.143237f, 1720.526f, 224.3622f, 14.62072f, 1712.374f, 230.3794f, -6.f, 98.66151f, 1846.07f, 173.6653f, 41.45658f, 1758.399f, 213.0361f, -30.f, 58.2f, 1729.6f, 228.1f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-437.4357f, -1196.306f, 52.99947f, -442.8505f, -1190.487f, 57.12535f, -6.f, -435.0204f, -1242.034f, 48.43407f, -448.8804f, -1342.776f, 30.26572f, -24.f, -462.6627f, -1212.356f, 58.3663f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(466.72f, 4319.375f, 59.95854f, 474.2116f, 4328.239f, 64.00435f, -8.f, 401.4681f, 4394.32f, 61.78275f, 450.5329f, 4342.308f, 66.88426f, 25.75f, 454.1235f, 4323.501f, 68.73932f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-166.3456f, 6578.911f, 12.05939f, -162.1356f, 6575.203f, 16.19019f, -6.f, -151.7565f, 6588.687f, 8.772982f, -55.48508f, 6689.387f, 14.51807f, -21.f, -166.0263f, 6588.806f, 11.69604f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-977.3154f, 4180.182f, 133.4073f, -969.1559f, 4188.988f, 138.6073f, -7.f, -1068.254f, 4267.542f, 101.9986f, -1008.683f, 4219.646f, 117.8451f, -24.f, -977.f, -4247.f, -144.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-7.579316f, -1037.718f, 37.53464f, -6.544167f, -1033.321f, 41.57407f, -8.f, -32.06438f, -1018.62f, 26.90977f, -100.7285f, -1024.356f, 29.27405f, 38.75f, -36.f, -1037.f, -47.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-268.0506f, -770.5955f, 55.124f, -270.5158f, -775.4097f, 60.10282f, -6.f, -213.3776f, -799.5538f, 28.45401f, -176.9494f, -812.3639f, 34.23903f, 25.75f, -163.4269f, -787.8375f, 53.7828f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-86.19047f, -537.1067f, 38.11981f, -81.48403f, -537.1505f, 43.90483f, -3.f, -102.1343f, -526.785f, 26.51042f, -177.5483f, -526.9933f, 32.5276f, -24.f, -113.f, -545.f, -45.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-1594.773f, -762.3895f, 20.85323f, -1603.425f, -727.0289f, 25.63661f, -8.f, -1634.038f, -735.4114f, 9.369503f, -1718.671f, -678.6514f, 14.0662f, 78.5f, -1610.f, -714.f, -22.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-248.6565f, -215.402f, 47.083f, -234.4291f, -206.4805f, 50.083f, -6.f, -288.7843f, -199.2215f, 36.63531f, -348.309f, -192.3793f, 41.15861f, 33.5f, -268.f, -223.f, -50.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-1442.916f, 403.0396f, 109.2874f, -1447.803f, 402.9255f, 114.2972f, -6.f, -1431.152f, 327.9755f, 60.38145f, -1443.336f, 247.949f, 63.55577f, 55.5f, -1474.f, 352.8f, 104.1f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(3351.987f, 5156.334f, 18.20752f, 3352.75f, 5148.515f, 24.13302f, -10.f, 3418.529f, 5166.281f, 3.857807f, 3445.439f, 5168.265f, 9.606205f, 32.25f, -3391.f, -5177.f, -18.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(1687.485f, 2340.26f, 73.36435f, 1674.006f, 2340.698f, 78.25781f, -6.f, 1685.363f, 2411.073f, 43.42663f, 1684.302f, 2434.852f, 48.56516f, -40.f, -1648.f, -2359.f, -80.f, 150, 0, 0);
	vVar2 = v3(319.f, -612.f, 45.f);
	JUMPS_MISC::ADD_STUNT_JUMP(307.3563f, -621.0101f, 42.3353f, 309.8869f, -619.0259f, 45.4455f, 334.0952f, -649.0976f, 27.6553f, 390.8702f, -627.327f, 30.9727f, vVar2.x, vVar2.y, vVar2.z, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-882.7947f, -854.2749f, 17.6236f, -884.027f, -849.2998f, 28.1236f, -9.f, -963.61f, -859.1973f, 11.98967f, -902.2921f, -857.7957f, 20.24098f, 38.25f, -910.f, -876.f, -25.f, 150, 0, 0);
	vVar2 = v3(366.f, -1150.f, 43.f);
	JUMPS_MISC::ADD_STUNT_JUMP(364.7186f, -1162.999f, 28.2918f, 374.8433f, -1153.451f, 34.7019f, 289.772f, -1195.962f, 37.1024f, 344.4012f, -1168.454f, 40.4272f, vVar2.x, vVar2.y, vVar2.z, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(396.1014f, -1656.237f, 48.00058f, 400.5907f, -1659.715f, 53.08016f, -8.f, 423.4009f, -1627.283f, 27.29182f, 448.9984f, -1594.914f, 32.30539f, 55.25f, -424.f, -1656.f, -51.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(52.47308f, -779.2045f, 42.21918f, 50.38058f, -784.9816f, 47.18962f, -6.f, 74.71162f, -792.1132f, 29.64289f, 119.4799f, -808.371f, 34.34875f, 24.5f, -73.f, -769.f, -46.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(32.60692f, 6526.098f, 29.62476f, 44.76025f, 6513.196f, 41.56066f, 13.5f, 28.0924f, 6507.57f, 29.43886f, -21.48365f, 6456.287f, 33.36642f, 32.25f, 1.0814f, 6495.755f, 39.2608f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(1789.045f, 2049.238f, 65.45301f, 1783.491f, 2044.977f, 68.84211f, -6.f, 1839.666f, 1912.061f, 56.96013f, 1806.044f, 1994.968f, 63.33834f, -20.f, -1774.f, -2030.f, -71.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-1070.755f, 10.70386f, 50.34879f, -1071.086f, 8.394933f, 55.37626f, -6.f, -1059.804f, 7.505019f, 59.62975f, -1042.759f, 4.53342f, 45.65608f, -3.f, -1062.f, -24.f, -63.f, 150, 0, 0);
	vVar0 = v3(89.6931f, -2191.275f, 5.747f);
	vVar1 = v3(30.7866f, -2192.573f, 5.1184f);
	vVar2 = v3(80.9447f, -2199.302f, 4.9105f);

	auto coord1 = func_76(vVar0, 0);
	auto coord2 = func_76(vVar0, 1);
	auto coord3 = func_75(vVar1, 0);
	auto coord4 = func_75(vVar1, 1);
	auto coord5 = func_75(vVar1, 1);

	JUMPS_MISC::ADD_STUNT_JUMP(coord1.x, coord1.y, coord1.z, coord2.x, coord2.y, coord2.z, coord3.x, coord3.y, coord3.z, coord5.x, coord5.y, coord5.z, vVar2.x, vVar2.y, vVar2.z, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(1637.904f, 3608.275f, 33.47485f, 1629.742f, 3603.816f, 42.63604f, 9.875f, 1590.551f, 3584.659f, 30.72894f, 1495.256f, 3532.62f, 40.86155f, 41.625f, -1557.f, -3589.f, -42.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(566.68f, -594.16f, 43.86801f, 564.135f, -594.5361f, 48.96004f, -6.f, 584.3754f, -656.7363f, 10.542f, 607.3912f, -744.896f, 15.90709f, -80.f, -550.f, -632.f, -45.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(452.9986f, -1374.922f, 43.02972f, 449.3213f, -1379.443f, 48.07609f, -6.f, 491.9446f, -1413.2f, 27.3054f, 557.421f, -1461.428f, 32.19254f, 46.5f, -495.f, -1397.f, -48.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-425.5986f, -1555.608f, 22.70676f, -418.9902f, -1557.324f, 31.41631f, 9.5f, -425.4729f, -1443.893f, 19.71997f, -430.4611f, -1535.311f, 28.21267f, 25.5f, -444.5202f, -1511.756f, 27.8632f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-963.1714f, -2778.506f, 14.47828f, -965.7361f, -2777.121f, 19.46395f, -8.f, -988.8297f, -2830.789f, 11.96478f, -1027.989f, -2895.436f, 16.95805f, -18.f, -967.196f, -2811.716f, 14.5521f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-2009.693f, -319.2802f, 47.54504f, -2000.673f, -306.3672f, 51.54504f, -8.f, -2102.132f, -241.9226f, 7.677715f, -2040.342f, -281.8877f, 26.53936f, 71.75f, -2060.904f, -251.8438f, 35.9419f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(1671.913f, 3151.226f, 45.29734f, 1680.949f, 3154.494f, 50.3022f, -6.f, 1658.687f, 3255.261f, 38.57218f, 1665.78f, 3198.186f, 46.24008f, 60.5f, -1651.f, -3166.f, -57.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-524.6519f, -1489.865f, 12.31534f, -521.7512f, -1477.948f, 17.32255f, -6.f, -499.4218f, -1491.98f, 8.405223f, -443.707f, -1514.7f, 15.50227f, 33.5f, -522.f, -1516.f, -17.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(787.837f, -2912.408f, 5.628719f, 787.8829f, -2910.002f, 10.59276f, -8.f, 734.1174f, -2910.26f, 3.919759f, 671.3137f, -2910.305f, 9.191636f, -14.f, -757.f, -2923.f, -20.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(1978.694f, 1925.877f, 87.246f, 1980.888f, 1942.735f, 96.48006f, 8.3125f, 1918.173f, 1913.685f, 55.10921f, 1900.403f, 2006.587f, 61.17362f, -31.f, 1928.212f, 1911.14f, 73.7466f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(672.2588f, -3003.404f, 6.047905f, 672.0038f, -3007.075f, 10.86605f, -6.f, 782.1926f, -2994.932f, 4.036896f, 732.1247f, -3005.69f, 11.83312f, 37.25f, -715.f, -3024.f, -20.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(108.1759f, -2815.123f, 9.17942f, 110.2545f, -2814.757f, 14.23679f, -6.f, 93.96964f, -2739.858f, 4.505202f, 82.31894f, -2706.242f, 7.005202f, 23.25f, -92.f, -2786.f, -15.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(109.0594f, -3209.312f, 7.463991f, 111.0596f, -3208.928f, 12.91259f, -6.f, 127.4547f, -3257.39f, 14.77992f, 128.4464f, -3311.17f, 19.44173f, -18.f, -108.f, -3292.f, -26.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(124.2149f, -2954.815f, 9.250035f, 122.1116f, -2955.03f, 14.26613f, -6.f, 128.9299f, -3006.801f, 15.47611f, 134.7525f, -3068.489f, 20.46475f, -22.f, -113.f, -2980.f, -19.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(174.6314f, -2782.512f, 7.013673f, 183.1974f, -2774.705f, 13.7502f, 3.25f, 260.693f, -2675.165f, 16.32216f, 231.2144f, -2747.909f, 18.90412f, -16.f, -188.f, -2749.f, -24.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(163.6802f, -2961.333f, 7.712487f, 165.7382f, -2960.979f, 12.76933f, -6.f, 142.2329f, -2895.039f, 12.95989f, 142.2177f, -2849.85f, 18.45989f, 28.25f, -173.f, -2918.f, -20.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(285.7501f, -3014.055f, 8.774601f, 288.3199f, -3013.423f, 13.83196f, -6.f, 274.9825f, -2988.799f, 3.447593f, 272.0995f, -2860.959f, 9.019781f, 60.75f, -284.f, -2968.f, -16.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(371.4717f, -2635.26f, 9.349143f, 371.6286f, -2637.314f, 14.39637f, -6.f, 506.0603f, -2627.234f, 4.586116f, 442.4721f, -2630.006f, 7.15538f, -18.f, -412.f, -2621.f, -21.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-854.3132f, -2551.837f, 20.41864f, -850.6099f, -2553.969f, 27.43327f, -6.f, -798.0812f, -2469.664f, 11.88453f, -885.4293f, -2483.408f, 23.94611f, 95.25f, -891.8524f, -2466.815f, 60.0357f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-986.5257f, -2507.188f, 20.45239f, -990.4862f, -2504.88f, 27.38469f, -6.f, -987.5785f, -2554.466f, 32.70585f, -1014.478f, -2600.25f, 40.10584f, 50.25f, -1023.f, -2516.f, -43.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-589.2717f, -1532.161f, 3.122784f, -587.6168f, -1526.171f, 6.213938f, -6.f, -704.963f, -1488.515f, 3.172576f, -763.7324f, -1463.675f, 6.000514f, 42.5f, -669.f, -1537.f, -33.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-626.5751f, -1075.897f, 21.0667f, -625.0385f, -1070.019f, 26.05841f, -7.f, -704.2628f, -1075.639f, 11.31195f, -668.6943f, -1051.684f, 17.63114f, 28.25f, -641.f, -1061.f, -25.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-453.6471f, -1397.42f, 30.32707f, -449.6354f, -1397.113f, 35.30394f, -6.f, -456.1882f, -1440.832f, 27.29717f, -454.3793f, -1482.426f, 34.73454f, 16.75f, -436.f, -1417.f, -39.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-445.2386f, -542.0142f, 24.50053f, -442.5161f, -542.0551f, 29.52355f, -6.f, -445.7004f, -442.1162f, 40.4093f, -445.1812f, -499.7989f, 20.82354f, 24.25f, -464.f, -526.f, -30.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-594.9152f, -109.8597f, 40.96681f, -600.7094f, -107.168f, 45.9851f, 3.375f, -625.0757f, -166.6679f, 35.66935f, -603.1118f, -120.366f, 40.4407f, 3.75f, -601.f, -124.f, -44.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(-726.3411f, -58.79087f, 39.67519f, -728.8365f, -54.57068f, 42.72398f, -3.f, -771.4631f, -75.39616f, 35.85175f, -855.1539f, -118.4413f, 40.32775f, -30.f, -737.f, -78.f, -46.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(1480.185f, -2218.538f, 77.75645f, 1478.212f, -2215.55f, 80.62068f, -3.f, 1429.022f, -2249.86f, 59.38379f, 1361.268f, -2295.879f, 68.70474f, 34.75f, -1457.f, -2255.f, -79.f, 150, 0, 0);
	JUMPS_MISC::ADD_STUNT_JUMP_ANGLED(367.1642f, -2522.259f, 6.246408f, 367.948f, -2525.47f, 10.87989f, -6.f, 401.6762f, -2508.97f, 10.13972f, 433.9243f, -2495.269f, 17.23942f, 25.75f, -376.f, -2490.f, -18.f, 150, 0, 0);
}

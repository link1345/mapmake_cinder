#pragma once
#include <cinder/CinderImGui.h>

/*! カラーネーム 140色 http://www.htmq.com/color/colorname.shtml */

namespace ColorPalette {
	using Color = ImVec4;

	// 驚きの汚さ。

	static const Color white = Color(255 / (float)255, 255 / (float)255, 255 / (float)255, 255 / (float)255);
	static const Color whitesmoke = Color(245 / (float)255, 245 / (float)255, 245 / (float)255, 255 / (float)255);
	static const Color ghostwhite = Color(248 / (float)255, 248 / (float)255, 255 / (float)255, 255 / (float)255);
	static const Color aliceblue = Color(240 / (float)255, 248 / (float)255, 255 / (float)255, 255 / (float)255);
	static const Color lavender = Color(230 / (float)255, 230 / (float)255, 250 / (float)255, 255 / (float)255);
	static const Color azure = Color(240 / (float)255, 255 / (float)255, 255 / (float)255, 255 / (float)255);
	static const Color lightcyan = Color(224 / (float)255, 255 / (float)255, 255 / (float)255, 255 / (float)255);
	static const Color mintcream = Color(245 / (float)255, 255 / (float)255, 250 / (float)255, 255 / (float)255);
	static const Color honeydew = Color(240 / (float)255, 255 / (float)255, 240 / (float)255, 255 / (float)255);
	static const Color ivory = Color(255 / (float)255, 255 / (float)255, 240 / (float)255, 255 / (float)255);
	static const Color beige = Color(245 / (float)255, 245 / (float)255, 220 / (float)255, 255 / (float)255);
	static const Color lightyellow = Color(255 / (float)255, 255 / (float)255, 224 / (float)255, 255 / (float)255);
	static const Color lightgoldenrodyellow = Color(250 / (float)255, 250 / (float)255, 210 / (float)255, 255 / (float)255);
	static const Color lemonchiffon = Color(255 / (float)255, 250 / (float)255, 205 / (float)255, 255 / (float)255);
	static const Color floralwhite = Color(255 / (float)255, 250 / (float)255, 240 / (float)255, 255 / (float)255);
	static const Color oldlace = Color(253 / (float)255, 245 / (float)255, 230 / (float)255, 255 / (float)255);
	static const Color cornsilk = Color(255 / (float)255, 248 / (float)255, 220 / (float)255, 255 / (float)255);
	static const Color papayawhite = Color(255 / (float)255, 239 / (float)255, 213 / (float)255, 255 / (float)255);
	static const Color blanchedalmond = Color(255 / (float)255, 235 / (float)255, 205 / (float)255, 255 / (float)255);
	static const Color bisque = Color(255 / (float)255, 228 / (float)255, 196 / (float)255, 255 / (float)255);
	static const Color snow = Color(255 / (float)255, 250 / (float)255, 250 / (float)255, 255 / (float)255);
	static const Color linen = Color(250 / (float)255, 240 / (float)255, 230 / (float)255, 255 / (float)255);
	static const Color antiquewhite = Color(250 / (float)255, 235 / (float)255, 215 / (float)255, 255 / (float)255);
	static const Color seashell = Color(255 / (float)255, 245 / (float)255, 238 / (float)255, 255 / (float)255);
	static const Color lavenderblush = Color(255 / (float)255, 240 / (float)255, 245 / (float)255, 255 / (float)255);
	static const Color mistyrose = Color(255 / (float)255, 228 / (float)255, 225 / (float)255, 255 / (float)255);
	static const Color gainsboro = Color(220 / (float)255, 220 / (float)255, 220 / (float)255, 255 / (float)255);
	static const Color lightgray = Color(211 / (float)255, 211 / (float)255, 211 / (float)255, 255 / (float)255);
	static const Color lightsteelblue = Color(176 / (float)255, 196 / (float)255, 222 / (float)255, 255 / (float)255);
	static const Color lightblue = Color(173 / (float)255, 216 / (float)255, 230 / (float)255, 255 / (float)255);
	static const Color lightskyblue = Color(135 / (float)255, 206 / (float)255, 250 / (float)255, 255 / (float)255);
	static const Color powderblue = Color(176 / (float)255, 224 / (float)255, 230 / (float)255, 255 / (float)255);
	static const Color paleturquoise = Color(175 / (float)255, 238 / (float)255, 238 / (float)255, 255 / (float)255);
	static const Color skyblue = Color(135 / (float)255, 206 / (float)255, 235 / (float)255, 255 / (float)255);
	static const Color mediumaquamarine = Color(102 / (float)255, 205 / (float)255, 170 / (float)255, 255 / (float)255);
	static const Color aquamarine = Color(127 / (float)255, 255 / (float)255, 212 / (float)255, 255 / (float)255);
	static const Color palegreen = Color(152 / (float)255, 251 / (float)255, 152 / (float)255, 255 / (float)255);
	static const Color lightgreen = Color(144 / (float)255, 238 / (float)255, 144 / (float)255, 255 / (float)255);
	static const Color khaki = Color(240 / (float)255, 230 / (float)255, 140 / (float)255, 255 / (float)255);
	static const Color palegoldenrod = Color(238 / (float)255, 232 / (float)255, 170 / (float)255, 255 / (float)255);
	static const Color moccasin = Color(255 / (float)255, 228 / (float)255, 181 / (float)255, 255 / (float)255);
	static const Color navajowhite = Color(255 / (float)255, 222 / (float)255, 173 / (float)255, 255 / (float)255);
	static const Color peachpuff = Color(255 / (float)255, 218 / (float)255, 185 / (float)255, 255 / (float)255);
	static const Color wheat = Color(245 / (float)255, 222 / (float)255, 179 / (float)255, 255 / (float)255);
	static const Color pink = Color(255 / (float)255, 192 / (float)255, 203 / (float)255, 255 / (float)255);
	static const Color lightpink = Color(255 / (float)255, 182 / (float)255, 193 / (float)255, 255 / (float)255);
	static const Color thistle = Color(216 / (float)255, 191 / (float)255, 216 / (float)255, 255 / (float)255);
	static const Color plum = Color(221 / (float)255, 160 / (float)255, 221 / (float)255, 255 / (float)255);
	static const Color silver = Color(192 / (float)255, 192 / (float)255, 192 / (float)255, 255 / (float)255);
	static const Color darkgray = Color(169 / (float)255, 169 / (float)255, 169 / (float)255, 255 / (float)255);
	static const Color lightslategray = Color(119 / (float)255, 136 / (float)255, 153 / (float)255, 255 / (float)255);
	static const Color slategray = Color(112 / (float)255, 128 / (float)255, 144 / (float)255, 255 / (float)255);
	static const Color slateblue = Color(106 / (float)255, 90 / (float)255, 205 / (float)255, 255 / (float)255);
	static const Color steelblue = Color(70 / (float)255, 130 / (float)255, 180 / (float)255, 255 / (float)255);
	static const Color mediumslateblue = Color(123 / (float)255, 104 / (float)255, 238 / (float)255, 255 / (float)255);
	static const Color royalblue = Color(65 / (float)255, 105 / (float)255, 225 / (float)255, 255 / (float)255);
	static const Color blue = Color(0 / (float)255, 0 / (float)255, 255 / (float)255, 255 / (float)255);
	static const Color dodgerblue = Color(30 / (float)255, 144 / (float)255, 255 / (float)255, 255 / (float)255);
	static const Color cornflowerblue = Color(100 / (float)255, 149 / (float)255, 237 / (float)255, 255 / (float)255);
	static const Color deepskyblue = Color(0 / (float)255, 191 / (float)255, 255 / (float)255, 255 / (float)255);
	static const Color cyan = Color(0 / (float)255, 255 / (float)255, 255 / (float)255, 255 / (float)255);
	static const Color aqua = Color(0 / (float)255, 255 / (float)255, 255 / (float)255, 255 / (float)255);
	static const Color turquoise = Color(64 / (float)255, 224 / (float)255, 208 / (float)255, 255 / (float)255);
	static const Color mediumturquoise = Color(72 / (float)255, 209 / (float)255, 204 / (float)255, 255 / (float)255);
	static const Color darkturquoise = Color(0 / (float)255, 206 / (float)255, 209 / (float)255, 255 / (float)255);
	static const Color lightseagreen = Color(32 / (float)255, 178 / (float)255, 170 / (float)255, 255 / (float)255);
	static const Color mediumspringgreen = Color(0 / (float)255, 250 / (float)255, 154 / (float)255, 255 / (float)255);
	static const Color springgreen = Color(0 / (float)255, 255 / (float)255, 127 / (float)255, 255 / (float)255);
	static const Color lime = Color(0 / (float)255, 255 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color limegreen = Color(50 / (float)255, 205 / (float)255, 50 / (float)255, 255 / (float)255);
	static const Color yellowgreen = Color(154 / (float)255, 205 / (float)255, 50 / (float)255, 255 / (float)255);
	static const Color lawngreen = Color(124 / (float)255, 252 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color chartreuse = Color(127 / (float)255, 255 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color greenyellow = Color(173 / (float)255, 255 / (float)255, 47 / (float)255, 255 / (float)255);
	static const Color yellow = Color(255 / (float)255, 255 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color gold = Color(255 / (float)255, 215 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color orange = Color(255 / (float)255, 165 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color darkorange = Color(255 / (float)255, 140 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color goldenrod = Color(218 / (float)255, 165 / (float)255, 32 / (float)255, 255 / (float)255);
	static const Color burlywood = Color(222 / (float)255, 184 / (float)255, 135 / (float)255, 255 / (float)255);
	static const Color tan = Color(210 / (float)255, 180 / (float)255, 140 / (float)255, 255 / (float)255);
	static const Color sandybrown = Color(244 / (float)255, 164 / (float)255, 96 / (float)255, 255 / (float)255);
	static const Color darksalmon = Color(233 / (float)255, 150 / (float)255, 122 / (float)255, 255 / (float)255);
	static const Color lightcoral = Color(240 / (float)255, 128 / (float)255, 128 / (float)255, 255 / (float)255);
	static const Color salmon = Color(250 / (float)255, 128 / (float)255, 114 / (float)255, 255 / (float)255);
	static const Color lightsalmon = Color(255 / (float)255, 160 / (float)255, 122 / (float)255, 255 / (float)255);
	static const Color coral = Color(255 / (float)255, 127 / (float)255, 80 / (float)255, 255 / (float)255);
	static const Color tomato = Color(255 / (float)255, 99 / (float)255, 71 / (float)255, 255 / (float)255);
	static const Color orangered = Color(255 / (float)255, 69 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color red = Color(255 / (float)255, 0 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color deeppink = Color(255 / (float)255, 20 / (float)255, 147 / (float)255, 255 / (float)255);
	static const Color hotpink = Color(255 / (float)255, 105 / (float)255, 180 / (float)255, 255 / (float)255);
	static const Color palevioletred = Color(219 / (float)255, 112 / (float)255, 147 / (float)255, 255 / (float)255);
	static const Color violet = Color(238 / (float)255, 130 / (float)255, 238 / (float)255, 255 / (float)255);
	static const Color orchid = Color(218 / (float)255, 112 / (float)255, 214 / (float)255, 255 / (float)255);
	static const Color magenta = Color(255 / (float)255, 0 / (float)255, 255 / (float)255, 255 / (float)255);
	static const Color fuchsia = Color(255 / (float)255, 0 / (float)255, 255 / (float)255, 255 / (float)255);
	static const Color mediumorchid = Color(186 / (float)255, 85 / (float)255, 211 / (float)255, 255 / (float)255);
	static const Color darkorchid = Color(153 / (float)255, 50 / (float)255, 204 / (float)255, 255 / (float)255);
	static const Color darkviolet = Color(148 / (float)255, 0 / (float)255, 211 / (float)255, 255 / (float)255);
	static const Color blueviolet = Color(138 / (float)255, 43 / (float)255, 226 / (float)255, 255 / (float)255);
	static const Color mediumpurple = Color(147 / (float)255, 112 / (float)255, 219 / (float)255, 255 / (float)255);
	static const Color gray = Color(128 / (float)255, 128 / (float)255, 128 / (float)255, 255 / (float)255);
	static const Color mediumblue = Color(0 / (float)255, 0 / (float)255, 205 / (float)255, 255 / (float)255);
	static const Color darkcyan = Color(0 / (float)255, 139 / (float)255, 139 / (float)255, 255 / (float)255);
	static const Color cadetblue = Color(95 / (float)255, 158 / (float)255, 160 / (float)255, 255 / (float)255);
	static const Color darkseagreen = Color(143 / (float)255, 188 / (float)255, 143 / (float)255, 255 / (float)255);
	static const Color mediumseagreen = Color(60 / (float)255, 179 / (float)255, 113 / (float)255, 255 / (float)255);
	static const Color teal = Color(0 / (float)255, 128 / (float)255, 128 / (float)255, 255 / (float)255);
	static const Color forestgreen = Color(34 / (float)255, 139 / (float)255, 34 / (float)255, 255 / (float)255);
	static const Color seagreen = Color(46 / (float)255, 139 / (float)255, 87 / (float)255, 255 / (float)255);
	static const Color darkkhaki = Color(189 / (float)255, 183 / (float)255, 107 / (float)255, 255 / (float)255);
	static const Color peru = Color(205 / (float)255, 133 / (float)255, 63 / (float)255, 255 / (float)255);
	static const Color crimson = Color(220 / (float)255, 20 / (float)255, 60 / (float)255, 255 / (float)255);
	static const Color indianred = Color(205 / (float)255, 92 / (float)255, 92 / (float)255, 255 / (float)255);
	static const Color rosybrown = Color(188 / (float)255, 143 / (float)255, 143 / (float)255, 255 / (float)255);
	static const Color mediumvioletred = Color(199 / (float)255, 21 / (float)255, 133 / (float)255, 255 / (float)255);
	static const Color dimgray = Color(105 / (float)255, 105 / (float)255, 105 / (float)255, 255 / (float)255);
	static const Color black = Color(0 / (float)255, 0 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color midnightblue = Color(25 / (float)255, 25 / (float)255, 112 / (float)255, 255 / (float)255);
	static const Color darkslateblue = Color(72 / (float)255, 61 / (float)255, 139 / (float)255, 255 / (float)255);
	static const Color darkblue = Color(0 / (float)255, 0 / (float)255, 139 / (float)255, 255 / (float)255);
	static const Color navy = Color(0 / (float)255, 0 / (float)255, 128 / (float)255, 255 / (float)255);
	static const Color darkslategray = Color(47 / (float)255, 79 / (float)255, 79 / (float)255, 255 / (float)255);
	static const Color green = Color(0 / (float)255, 128 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color darkgreen = Color(0 / (float)255, 100 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color darkolivegreen = Color(85 / (float)255, 107 / (float)255, 47 / (float)255, 255 / (float)255);
	static const Color olivedrab = Color(107 / (float)255, 142 / (float)255, 35 / (float)255, 255 / (float)255);
	static const Color olive = Color(128 / (float)255, 128 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color darkgoldenrod = Color(184 / (float)255, 134 / (float)255, 11 / (float)255, 255 / (float)255);
	static const Color chocolate = Color(210 / (float)255, 105 / (float)255, 30 / (float)255, 255 / (float)255);
	static const Color sienna = Color(160 / (float)255, 82 / (float)255, 45 / (float)255, 255 / (float)255);
	static const Color saddlebrown = Color(139 / (float)255, 69 / (float)255, 19 / (float)255, 255 / (float)255);
	static const Color firebrick = Color(178 / (float)255, 34 / (float)255, 34 / (float)255, 255 / (float)255);
	static const Color brown = Color(165 / (float)255, 42 / (float)255, 42 / (float)255, 255 / (float)255);
	static const Color maroon = Color(128 / (float)255, 0 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color darkred = Color(139 / (float)255, 0 / (float)255, 0 / (float)255, 255 / (float)255);
	static const Color darkmagenta = Color(139 / (float)255, 0 / (float)255, 139 / (float)255, 255 / (float)255);
	static const Color purple = Color(128 / (float)255, 0 / (float)255, 128 / (float)255, 255 / (float)255);
	static const Color indigo = Color(75 / (float)255, 0 / (float)255, 130 / (float)255, 255 / (float)255);
}

/*
namespace TerrainColor {
	static Color Default = ColorPalette::white;

	static Color Mountain = ColorPalette::sienna;
	static Color FlatLand = ColorPalette::greenyellow;
}
*/
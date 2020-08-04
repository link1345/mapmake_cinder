#pragma once

#include <cmath>
#include <thread>
#include <list>

#include <cinder/Rand.h> 
#include <cinder/gl/gl.h>
#include <cinder/Log.h>

using namespace std;

using namespace ci;
using namespace ci::gl;


/*! ホワイトノイズ
*/
class WhiteNoise {
public:
	WhiteNoise() {
		this->setup( vec2(500,500) );
		this->_Random();
	};

	/*! @brief アニメーションさせるか？ */
	bool anime = false;

	/*! @brief ここを変動させると、アニメーションが出来ます。
	@note whiteNoise以外は、重いので、アニメーションはダメ。やるならgpuで… */
	float u_time = 0;

	/*! @brief 1つの画像を毎回動かす毎に、別の乱数で回すか？ */
	bool NextRandomFlag = true;

	/*! @brief fBmのオクターブ値 */
	int octave = 3;

	/*! どのぐらい拡大するか
	@note 正確には、sin波みたいな曲線の波を緩やかにするか？である。 */
	float frequency = 0.2;

	/*! @brief fBmのgain値 */
	float gain = 0.5;

	/*! @brief fBmのlacunarity値 */
	float lacunarity = 3.0;

	/*! @brief fBmのamplitude値
	@note 画面の明るさが変わる感じ。(下上げるをする感じ) */
	float amplitude = 0.5;

	float Random(vec2 v) {
		//return fract(sin(dot(v, vec2(12.9898, 58.233))) * 43758.5453);
		return fract(sin(dot(v, rand_num)) * 43758.5453);
	}

	void Seed() {
		rand = Rand();
	}
	void Seed(int seed) {
		rand.seed(seed);
	}

	float animation(float f)
	{
		/* 0.0..1.0をsin波の周期で繰り返す
		(繰り返すのが目標ならこれでおｋなら、継続的に行うなら) */
		return sin(f * 6.283 + u_time * 2.0) * 0.5 + 0.5;
	}


	Color8u color(float num) {
		auto n = num * 255;
		return Color8u(n, n, n);
	}

	virtual float make(vec2 xy)
	{
		//return animation(random(xy));
		return Random(xy);
			
	}

	virtual float fBm(vec2 xy) {

		float amplitude = this->amplitude;

		// Initial values
		float num = 0.0;

		// Loop of octaves
		for (int i = 0; i < octave; i++) {
			num += amplitude * make(vec2(xy.x, xy.y) * frequency);
			xy = vec2(xy.x * lacunarity, xy.y * lacunarity);
			amplitude *= gain;
		}

		return num;
	}

	void setup(vec2 size) {
		// 画像サイズ設定。
		image = Surface(size.x, size.y ,true);
		anime = false;
	}


	/*! 
	@brief ドット絵作成例。
	@attention 絶対にこのドット１つ１つの処理をスレッドにするな！\n
	１つあたりの処理があまりにも小さすぎるため、スレッド作る時間と中身の時間を比較すると、スレッド作る方が遥かに時間が掛かる。
	cellなどの重い処理の場合なら、125,000ドット(500*250)ぐらいの数ずつやるのがベストか？
	@note あくまでテクスチャにした場合のものである為、１ドットずつ作りたければ、fBm関数どうぞ。
	*/
	void run() {
		
		for (int x = 0; x < image.getSize().x; x++) {
			for (int y = 0; y < image.getSize().y; y++) {
				
				float num = 0.0f;
				if (this->anime == false) {
					num = fBm(vec2(x, y));
				}
				else {
					num = animation(fBm(vec2(x, y)));
				}
				/* // domain warping だが…だが、ここではCPU処理なので、重すぎて動きません＼(^o^)／
					vec2 st = vec2(x, y);
					vec2 q = vec2(0.);
					q.x = fBm(
						vec2(st.x + 0.00 * u_time, st.y + 0.00 * u_time)
					);
					q.y = fBm(st + vec2(1.0));

					vec2 r = vec2(0.);
					r.x = fBm(
						vec2(st.x + 1.0 * q.x + 1.7 + 0.15 * u_time,
							st.y + 1.0 * q.y + 0.2 + 0.15 * u_time)
							);
					r.x = fBm(
						vec2(st.x + 1.0 * q.x + 8.3 + 0.126 * u_time,
							st.y + 1.0 * q.y + 2.8 + 0.126 * u_time)
					);
					float num = fBm(st + r);
					*/

				this->image.setPixel(vec2(x, y), color(num));
				
			}
		}

	}

	void update() {
		if (NextRandomFlag == true) {
			this->_Random();
		}

		if (this->anime != false) {
			this->image = Surface(image.getSize().x, image.getSize().y,true);
			this->run();
			u_time += 0.1;
		}
	}

	void draw() {
		auto t =  gl::Texture::create(this->image);
		gl::draw(t);
	}

	Surface image;

private:
	Rand rand = Rand();
	vec2 rand_num = vec2();

	void _Random() {
		rand_num = rand.nextVec2();
	}
};

class BlockNoise : public WhiteNoise{
public:

	vec2 blockSize = vec2(0.03,0.03);

	float make(vec2 xy) override{
		vec2 i_uv = vec2(floorf(xy.x * blockSize.x), floorf(xy.y * blockSize.y));
		return animation(Random(i_uv));

	}
};

class ValueNoise : public WhiteNoise {
public:
	vec2 iBlockSize = vec2(0.03,0.03);
	vec2 fBlockSize = vec2(0.03,0.03);

	float s = 3.0;
	float n = 2.0;

	void setBlockSize(float size) {
		this->iBlockSize = vec2(size, size);
		this->fBlockSize = vec2(size, size);
	}

	void setBlockSize(vec2 size) {
		this->iBlockSize = size;
		this->fBlockSize = size;
	}

	float interpolation(float f)
	{
		/* 0.0..1.0の補間式、5次のものがアーティファクト少なくていいらしい */
		/*return f * f * (3.0 - 2.0 * f);*/
		//return f * f * f * (f * (6.0 * f - 15.0) + 10.0);

		return f* f* (s - n * f);
	}

	float make(vec2 xy) override {
		vec2 i_uv = vec2(floorf(xy.x * iBlockSize.x), floorf(xy.y * iBlockSize.y));
		vec2 f_uv = vec2(fract(xy.x * fBlockSize.x), fract(xy.y * fBlockSize.y));

		float f1 = animation(Random(i_uv + vec2(0.0, 0.0)));
		float f2 = animation(Random(i_uv + vec2(1.0, 0.0)));
		float f3 = animation(Random(i_uv + vec2(0.0, 1.0)));
		float f4 = animation(Random(i_uv + vec2(1.0, 1.0)));
		float num = mix(
			mix(f1, f2, interpolation(f_uv.x)),
			mix(f3, f4, interpolation(f_uv.x)),
			interpolation(f_uv.y));

		return num;
	}
};

class PerlinNoise : public ValueNoise {
public:
	float ss = 2.0;
	float nn = 1.0;

	vec2 random2(vec2 v)
	{
		return vec2(Random(v), Random(v + vec2(0.5, 0.5)));
	}
	vec2 animation2(vec2 v)
	{
		return vec2(animation(v.x), animation(v.y));
	}

	float make(vec2 xy) override {
		vec2 i_uv = vec2(floorf(xy.x * iBlockSize.x), floorf(xy.y * iBlockSize.y));
		vec2 f_uv = vec2(fract(xy.x * fBlockSize.x), fract(xy.y * fBlockSize.y));

		auto s = random2(i_uv + vec2(0.0, 0.0));
		vec2 v1 = vec2(s.x * ss - nn,s.y * ss - nn);

		s = random2(i_uv + vec2(1.0, 0.0));
		vec2 v2 = vec2(s.x * ss - nn, s.y * ss - nn);

		s = random2(i_uv + vec2(0.0, 1.0));
		vec2 v3 = vec2(s.x * ss - nn, s.y * ss - nn);

		s = random2(i_uv + vec2(1.0, 1.0));
		vec2 v4 = vec2(s.x * ss - nn, s.y * ss - nn);

		float num = mix(
			mix(dot(v1, f_uv - vec2(0.0, 0.0)), dot(v2, f_uv - vec2(1.0, 0.0)), interpolation(f_uv.x)),
			mix(dot(v3, f_uv - vec2(0.0, 1.0)), dot(v4, f_uv - vec2(1.0, 1.0)), interpolation(f_uv.x)),
			interpolation(f_uv.y)) * 0.5 + 0.5;

		return num;
	}
};

class CellularNoise : public PerlinNoise {

	float make(vec2 xy) override {
		float num = 1.0;
		vec2 i_uv = vec2(floorf(xy.x * iBlockSize.x), floorf(xy.y * iBlockSize.y));
		vec2 f_uv = vec2(fract(xy.x * fBlockSize.x), fract(xy.y * fBlockSize.y));
		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				vec2 neightbor = vec2(float(x), float(y));
				vec2 r = random2(i_uv + neightbor);


				r = animation2(random2(vec2(r.x * ss,r.y * ss) + vec2(nn, nn)));

				r.x = max(min(r.x, 1.0f), 0.0f);
				r.y = max(min(r.y, 1.0f), 0.0f);
				
				num = min(length(f_uv - (neightbor + r)), num);
			}
		}
	
		return num;
	}
};


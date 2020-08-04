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


/*! �z���C�g�m�C�Y
*/
class WhiteNoise {
public:
	WhiteNoise() {
		this->setup( vec2(500,500) );
		this->_Random();
	};

	/*! @brief �A�j���[�V���������邩�H */
	bool anime = false;

	/*! @brief ������ϓ�������ƁA�A�j���[�V�������o���܂��B
	@note whiteNoise�ȊO�́A�d���̂ŁA�A�j���[�V�����̓_���B���Ȃ�gpu�Łc */
	float u_time = 0;

	/*! @brief 1�̉摜�𖈉񓮂������ɁA�ʂ̗����ŉ񂷂��H */
	bool NextRandomFlag = true;

	/*! @brief fBm�̃I�N�^�[�u�l */
	int octave = 3;

	/*! �ǂ̂��炢�g�傷�邩
	@note ���m�ɂ́Asin�g�݂����ȋȐ��̔g���ɂ₩�ɂ��邩�H�ł���B */
	float frequency = 0.2;

	/*! @brief fBm��gain�l */
	float gain = 0.5;

	/*! @brief fBm��lacunarity�l */
	float lacunarity = 3.0;

	/*! @brief fBm��amplitude�l
	@note ��ʂ̖��邳���ς�銴���B(���グ������銴��) */
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
		/* 0.0..1.0��sin�g�̎����ŌJ��Ԃ�
		(�J��Ԃ��̂��ڕW�Ȃ炱��ł����Ȃ�A�p���I�ɍs���Ȃ�) */
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
		// �摜�T�C�Y�ݒ�B
		image = Surface(size.x, size.y ,true);
		anime = false;
	}


	/*! 
	@brief �h�b�g�G�쐬��B
	@attention ��΂ɂ��̃h�b�g�P�P�̏������X���b�h�ɂ���ȁI\n
	�P������̏��������܂�ɂ����������邽�߁A�X���b�h��鎞�Ԃƒ��g�̎��Ԃ��r����ƁA�X���b�h�������y���Ɏ��Ԃ��|����B
	cell�Ȃǂ̏d�������̏ꍇ�Ȃ�A125,000�h�b�g(500*250)���炢�̐������̂��x�X�g���H
	@note �����܂Ńe�N�X�`���ɂ����ꍇ�̂��̂ł���ׁA�P�h�b�g����肽����΁AfBm�֐��ǂ����B
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
				/* // domain warping �����c�����A�����ł�CPU�����Ȃ̂ŁA�d�����ē����܂���_(^o^)�^
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
		/* 0.0..1.0�̕�Ԏ��A5���̂��̂��A�[�e�B�t�@�N�g���Ȃ��Ă����炵�� */
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


/*
 * Copyright(C) 2018 Alysson Ribeiro da Silva
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see<https://www.gnu.org/licenses/>.
 *
*/

#ifndef SIMPLEALGEBRA_H
#define SIMPLEALGEBRA_H

#include <algorithm>
#include <math.h>

using namespace std;

namespace Algebra {
	//------------------------------------------------------------------------------------------------------------
	typedef struct ivec {
		int x, y;
		double z, w;
		//--------------------------------------------------------------------------------------------------------
		ivec() {
			x = 0;
			y = 0;
			z = 0.0;
			w = 0.0;
		}
		//--------------------------------------------------------------------------------------------------------
		ivec(int x, int y) {
			this->x = x;
			this->y = y;
			z = 0.0;
			w = 0.0;
		}
		//--------------------------------------------------------------------------------------------------------
		ivec(int x, int y, double z) {
			this->x = x;
			this->y = y;
			this->z = z;
			w = 0.0;
		}
		//--------------------------------------------------------------------------------------------------------
		ivec(int x, int y, double z, double w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		//--------------------------------------------------------------------------------------------------------
		ivec& operator=(const ivec& value) {
			this->x = value.x;
			this->y = value.y;
			this->z = value.z;
			this->w = value.w;
			return *this;
		}
		//--------------------------------------------------------------------------------------------------------
		bool operator==(const ivec& value) {
			if (this->x == value.x && this->y == value.y)
				return true;
			return false;
		}
		//--------------------------------------------------------------------------------------------------------
		bool operator!=(const ivec& value) {
			if (this->x == value.x && this->y == value.y)
				return false;
			return true;
		}
		//--------------------------------------------------------------------------------------------------------
		double manhattan2D(const ivec& value) {
			return abs(value.x - x) + abs(value.y - y);
		}
		//--------------------------------------------------------------------------------------------------------
		double euclid2D(const ivec& value) {
			return sqrt(pow(value.x - x, 2.0) + pow(value.y - y, 2.0));
		}
		//--------------------------------------------------------------------------------------------------------
		double octile2D(const ivec& value) {
			return max(abs(value.x - x), abs(value.y - y)) + 0.5 * min(abs(value.x - x), abs(value.y - y));
		}
	}ivec;
}
#endif

/*
 * pi12_20220217_sparse_list.cpp
 *
 *  Created on: Feb 17, 2022
 *      Author: KZ
 */

#include <iostream>
#include <random>
//using namespace std;

namespace pi12_20220217_sparse_list {

const int NN=10000, KK=800;

int generate_random(double probability_of_zero, int max_value) {
	static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dist_int(1, max_value);
    static std::uniform_real_distribution<> dist_real(0, 1);

    double rand_prob = dist_real(gen);
    if (rand_prob < probability_of_zero ) { return 0; }
    else { return dist_int(gen); }

}

int generate_random_int(int max_value, int min_value = 1) {
	static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dist(min_value, max_value);

    return dist(gen);

}


int get_vector_product_original() {
	  int i, inp, sum;
	  struct {int nm, val;} M[KK], *p;
	  p = M;
	  std::size_t count = 0;
	  for (i=0; i<NN; i++) {
	  	  inp = generate_random((double)KK/NN, 100);

	  	  if (p->val = inp)  {
	  		  if (count >= KK) { break; }
	  		  (p++)->nm = i;
	  		  count++;
	  	  }
	  	}
	  p->nm = NN; sum = 0; p = M;
	  for (i=0; i<NN; i++) {
		  inp = generate_random((double)KK/NN, 100);
	  	if (i == p->nm) sum += (p++)->val * inp;
	  }
	  return sum;
}

int get_vector_product_small_loop() {
	  int i, inp, sum;
	  struct {int nm, val;} M[KK], *p;
	  p = M;
	  std::size_t count = 0;
	  for (i=0; i<KK; i++) {
	  	  inp = generate_random_int(100);
	  	  int last_index = 0;
	  	  if (i>0) last_index = M[i-1].nm;
	  	  int expected_step = (NN - last_index) / (KK - i);
	  	  int actual_step = generate_random_int(expected_step);
	  	  //std::cout<<expected_step<<" "<<actual_step<<" "<<last_index<<" ";
	  	  M[i].val = inp;
	  	  M[i].nm = last_index + actual_step;
	  	  std::cout<<"index =" <<M[i].nm<<", val="<<M[i].val<<std::endl;

	  	}
	  return 0;
	  p->nm = NN; sum = 0; p = M;
	  for (i=0; i<NN; i++) {
		  inp = generate_random((double)KK/NN, 100);
	  	if (i == p->nm) sum += (p++)->val * inp;
	  }
	  return sum;
}

int main() {

  std::cout << "SUM = " << get_vector_product_original() << std::endl;
  get_vector_product_small_loop();
  return 0;
}

}

#include "Topology.hpp"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	int N(atoi(argv[1])),k(atoi(argv[2])),i,rnow(0),rtarget;

	if(**(argv+3) == 'D'){//it's a Dynamic ring.
		vector<int> r;
		for(i=0;i<atoi(argv[4]);i++)
			r.push_back(atoi(argv[5+i]));
		Topology dr(N, k, 0);//construct class.
		for(i=0;i<50;i++){
			//set rnow to correct value.
			rtarget = i/5 >= r.size()-1?r.back():r[i/5];
			if(!(i%3)&&rnow<rtarget)
				rnow++;		
			//cycle, plot and save data into txt.
			dr.cycle(N,k);
			if(i==0||i==4||i==9||i==14||i==49){
				dr.filelist(N, k, "D", i+1);
				dr.ringplot(N, k, rnow, r.back(), "D", i+1);
			}
			dr.calculate_dos(rnow);
		}
		dr.filedos(N, k, "D");
	}

	else if(**(argv+3) == 'B'){// It's a binary tree!
		Topology dr(N, k);
		for(i=0;i<50;i++){
			dr.cycle(N,k);
			if(i==0||i==4||i==9||i==14||i==49){
				dr.filelist(N, k, "B", i+1);
				dr.BRtreeplot(N, k, "B", i+1);
			}
			dr.calculate_dos(1);
		}
		dr.filedos(N, k, "B");
	}
	else if(**(argv+3) == 'C'){// it's a crescent moon!
		Topology dr(N, k, 'C');
		for(i=0;i<50;i++){
			dr.cycle(N,k);
			if(i==0||i==4||i==9||i==14||i==49){
				dr.filelist(N, k, "C", i+1);
				dr.moonplot(N, k, 400, "C", i+1);
			}
			dr.calculate_dos(400);
		}
		dr.filedos(N, k, "C");
		
	}
	else
		cout << "wrong topology type" << endl;
	
	return 0;
}
// Defination of class Topology
#include "Topology.hpp"

//constructor of Dynamic ring
Topology::Topology(int N, int k, int r){
	int i,j;

	//nodes are equally distributed on the ring.
	//stores the angle value for each node.
	for(i=0;i<N;++i)
		theta.push_back((float)i/N *2*3.141592654);

	//initialize neighbor for each node randomly
	for(i=0;i<N;i++)
		random.push_back(i);
	for(i=0;i<N;i++){
		random_shuffle(random.begin(),random.end());
		vector<int> temp(random.begin(),random.begin()+k);
		list.push_back(temp);
	}

	//calculate the distance and fill up the distance chart
	for(i=0;i<N;i++){
		vector<float> temp;
		for(j=0;j<N;j++)
			temp.push_back(ring_distance(theta[i],theta[j]));
		chart.push_back(temp);
	}

};

//constructor of binary tree topology.
Topology::Topology(int N, int k){
	int i,j;
	for(i=0;i<N;i++)
		random.push_back(i);
	for(i=0;i<N;i++){
		random_shuffle(random.begin(),random.end());
		vector<int> temp(random.begin(),random.begin()+k);
		list.push_back(temp);
	}
	for(i=0;i<N;i++){
		vector<float> temp;
		for(j=0;j<N;j++)
			temp.push_back((float)BRtree_distance(i+1,j+1));
		chart.push_back(temp);
	}
}

//constructor of crescent moon
Topology::Topology(int N, int k, char type){
	int i,j;
	float x,y;
	float angle;

	/*calcaute coordinate of nodes. assuming that crescent moon is
	created by overlapping two circles with diffenrent radius.
	In this case, I assume radius of first circle is 1 and radius for
	another circle is sqrt(3). They are all on x-axis and the distance
	between their centre point is 1. I use the vertical line between 
	two sharp point on the crescnet moon as y-axis. So you can find the
	zero point of this plane. You can do some test to visualize it.*/
	for(i=0;i<N/2;++i){
		angle = (2 * (float)i / N + 1) * 2 * 3.141592654/ 3;
		x = cos(angle) + 0.5;
		y = sin(angle);
		vector<float> temp;
		temp.push_back(x);
		temp.push_back(y);
		nodes.push_back(temp);
	}
	for(i=0;i<N/2;++i){
		angle = 2 * 3.141592654 * (float)i / (3 * N) + 3.141592654 * 5 / 6 ;
		x = (cos(angle) + cos (3.141592654 / 6 )) * 2 * sin(3.141592654 / 3);
		y = sin(angle) * 2 * sin(3.141592654 / 3);
		vector<float> temp;
		temp.push_back(x);
		temp.push_back(y);
		nodes.push_back(temp);
	}
	for(i=0;i<N;i++)
		random.push_back(i);
	for(i=0;i<N;i++){
		random_shuffle(random.begin(),random.end());
		vector<int> temp(random.begin(),random.begin()+k);
		list.push_back(temp);
	}
	for(i=0;i<N;i++){
		vector<float> temp;
		for(j=0;j<N;j++)
			temp.push_back(moon_distance(nodes[i][0],nodes[i][1],nodes[j][0],nodes[j][1], i, j, N));
		chart.push_back(temp);
	}
}

//calculatiing distance betwwen nodes with anle theta1 and theta2 on dynamic ring.
float Topology::ring_distance(float theta1, float theta2){
	return sqrt(pow(sin(theta1)-sin(theta2),2)+pow(cos(theta2)-cos(theta1),2));
}

//calculating distance between node#a and node#b.
int Topology::BRtree_distance(int a, int b){
	int bits = 32; 
	int alevel=bits; 
	int blevel=bits; 
	int commonprefix=0;
	int mask = 1 << bits-1;
	// find the level of node a
	while((mask&a)==0){ 
		a <<= 1; 
		alevel--; 
	}
	// find the level of node b 
	while((mask&b)==0){
		b <<= 1;
		blevel--;
	}
	int length = min(alevel,blevel);
	while((mask&~(a^b))!=0&&length>0){
		b <<= 1;
		a <<= 1;
		commonprefix++;
		length--;
	}
	return alevel - commonprefix + blevel - commonprefix; 

}

/*I define the distance between two nodes on moon as Euclidean distance.
  However, if these two nodes are on different sides of that moon,
  their distance will be times 1000. By doing this, I make the distance
  between nodes on different sides very large. So the connection between 
  them will be highly likely discarded.*/
float Topology::moon_distance(float x1, float y1, float x2, float y2, int i, int j, int N){
	float dis;
	dis = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	if(i<N/2){
		if(j>N/2)
			dis = dis * 1000;
	}
	else{
		if(j<N/2)
			dis = dis * 1000;
	}
	return dis;
}

//run for one cycle.
void Topology::cycle(int N, int k){
	int i,j,z;
	srand(time(0));//use system time as random seed.
	for(i=0;i<N;i++){
		while(i==(j = (long)rand() * N/RAND_MAX)); 
		vector<int> temp = list[i];

		//combine the neighbors maintained by node i and node j.
		temp.push_back(i);
		temp.push_back(j);
		for(z=0;z<list[j].size();z++)
			temp.push_back(list[j][z]);

		sort(temp.begin(),temp.end()); 
		temp.erase(unique(temp.begin(),temp.end()),temp.end());//erase repeated value.
		
		//look up for the chart and insert distance into ditemp/djtemp
		vector<float> ditemp,djtemp;
		for(z=0;z<temp.size();z++){
			ditemp.push_back(chart[i][temp[z]]);
			djtemp.push_back(chart[j][temp[z]]);
			//node can't connect to itself. so set the distance to max.
			if(i==temp[z])	ditemp[z] = numeric_limits<float>::max();
			if(j==temp[z])	djtemp[z] = numeric_limits<float>::max();
		}
		dsort(temp, ditemp, i, k);
		dsort(temp, djtemp, j, k);
	}
}

//customized function to sort distance
void Topology::dsort(vector<int> nodes, vector<float> dvec, int target, int k){
	int i,j;
	//empty the target column in list.
	list[target].erase(list[target].begin(),list[target].end());

	//bubble sort within.
	for(i=0;i<k;i++){
		for(j=dvec.size()-1;j>i;j--){
			if(dvec[j]<dvec[j-1]){
				swap(dvec[j],dvec[j-1]);
				swap(nodes[j],nodes[j-1]);
			}
		}
		//generate new neighbors with minimized distance.
		list[target].push_back(nodes[i]);
	}
}

//take the data from the list and file them into text.
void Topology::filelist(int N, int k, string type, int iteration){
	string filename = type + "_N" + ntos(N) + "_k" + ntos(k) + "_" + ntos(iteration) + ".txt";
	ofstream outfile(filename.c_str());
	outfile << "nodeID" << ' ' << "neighbors" << endl;
	int i,j;
	for(i=0;i<N;i++){
		outfile << i;
		for(j=0;j<k;j++)
			outfile << ' ' << list[i][j];
		outfile << endl;
	}
	outfile.close();
}

//customized function of converting int to string
string Topology::ntos(int a){
	ostringstream temp;
    temp<<a;
    return temp.str();
}

//calculate distance of sum.
void Topology::calculate_dos(int r){
	int i,j;
	float dos(0);
	for(i=0;i<list.size();i++){
		for(j=0;j<list[i].size();j++)
			dos += r*chart[i][list[i][j]];
	}
	distance_sum.push_back(dos);
}

//take data from distance_sum and file them into text.
void Topology::filedos(int N, int k, string type){
	string filename = type + "_N" + ntos(N) + "_k" + ntos(k) + ".txt";
	ofstream outfile(filename.c_str());
	outfile << "cycle#" << " " << "sum of distance" << endl;
	int i;
	for(i=0;i<distance_sum.size();i++)
		outfile << i << ' ' << distance_sum[i] << endl;
	outfile.close();
}

//plotting function for dynamic ring.
void Topology::ringplot(int N, int k,int r, int maxr, string type, int iteration){
	BMP img;//initialize a BMP class.
	img.SetSize(1000, 1000);//set pixel size to 1000 x 1000.
	int i,j,x1,x2,y1,y2;
	float radius = ((float)r/maxr * 400);
	string filename;

	//plot nodes.
	for(i=0;i<theta.size();i++){
		x1 = (int)(cos(theta[i])*radius) + 500;
		y1 = (int)(sin(theta[i])*radius) + 500;
		img(x1,y1)->Red = 0;
		img(x1,y1)->Blue = 0;
		img(x1,y1)->Green = 0;
		img(x1,y1)->Alpha = 0;
	}

	//plot connecting lines between nodes.
	for(i=0;i<list.size();i++){
		for(j=0;j<list[i].size();j++){
			x1 = (int)(cos(theta[i])*radius) +500;
			x2 = (int)(cos(theta[list[i][j]])*radius) + 500;
			y1 = (int)(sin(theta[i])*radius) + 500;
			y2 = (int)(sin(theta[list[i][j]])*radius) + 500;
			line(x1, y1, x2, y2, img);
		}
	}


	filename = type + "_N" + ntos(N) + "_k" + ntos(k) + "_" + ntos(iteration) + ".bmp";
	img.WriteToFile(filename.c_str());
}

void Topology::BRtreeplot(int N, int k, string type, int iteration){
	BMP img;
	img.SetSize(1000, 1000);
	int i,j,x1,x2,y1,y2,product(1),totallevel,l1,l2;
	string filename;

	//calculate the total levels of these nodes when forming a binary tree.
	for(i=1;product<N;i++)
		product = product * 2;
	totallevel = i;

	// plot nodes
	for(i=0;i<N;i++){
		l1 = level(i);
		x1 = 100 + 800 / pow(2,l1+1) * (3 + 2 * (i - pow(2,l1)));
		y1 = 100 + 800 / (totallevel - 1) * l1;
		img(x1,y1)->Red = 0;
		img(x1,y1)->Blue = 0;
		img(x1,y1)->Green = 0;
		img(x1,y1)->Alpha = 0;
	}
	
	//plot connecting lines.
	for(i=0;i<list.size();i++){
		for(j=0;j<list[i].size();j++){
			l1 = level(i);
			l2 = level(list[i][j]);
			x1 = 100 + 800 / pow(2,l1+1) * (3 + 2 * (i - pow(2,l1)));
			x2 = 100 + 800 / pow(2,l2+1) * (3 + 2 * (list[i][j] - pow(2,l2)));
			y1 = 100 + 800 / (totallevel - 1) * l1;
			y2 = 100 + 800 / (totallevel - 1) * l2;
			line(x1, y1, x2, y2, img);
		}
	}


	filename = type + "_N" + ntos(N) + "_k" + ntos(k) + "_" + ntos(iteration) + ".bmp";
	img.WriteToFile(filename.c_str());
}

void Topology::moonplot(int N, int k, int r, string type, int iteration){
	BMP img;
	img.SetSize(1000, 1000);
	int i,j,x1,y1,x2,y2;
	string filename;

	for(i=0;i<N;i++){
		x1 = (int)(500 + r * nodes[i][0]);
		y1 = (int)(500 + r * nodes[i][1]);
		img(x1,y1)->Red = 0;
		img(x1,y1)->Blue = 0;
		img(x1,y1)->Green = 0;
		img(x1,y1)->Alpha = 0;
	}
	for(i=0;i<list.size();i++){
		for(j=0;j<list[i].size();j++){
			x1 = (int)(500 + r * nodes[i][0]);
			x2 = (int)(500 + r * nodes[list[i][j]][0]);
			y1 = (int)(500 + r * nodes[i][1]);
			y2 = (int)(500 + r * nodes[list[i][j]][1]);
			line(x1, y1, x2, y2, img);
		}
	}

	filename = type + "_N" + ntos(N) + "_k" + ntos(k) + "_" + ntos(iteration) + ".bmp";
	img.WriteToFile(filename.c_str());
}

//calculate the current level for node 
int Topology::level(int i){
	int a;
	for(a=0;i>=pow(2,a+1)-1;a++){};
	return a; 
}

//// Bresenham's line algorithm. Drawing a line between 2 nodes with coordinates.
void Topology::line(int x1, int y1, int const x2, int const y2, BMP& img){
	
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = abs(delta_x) << 1;
 	int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = abs(delta_y) << 1;
 
    if (delta_x >= delta_y){
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
 
        while (x1 != x2){
            if ((error >= 0) && (error || (ix > 0))){
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing
 
            error += delta_y;
            x1 += ix;
 
            img(x1,y1)->Red = 0;
			img(x1,y1)->Blue = 0;
			img(x1,y1)->Green = 0;
			img(x1,y1)->Alpha = 0;
        }
    }
    else{
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
 
        while (y1 != y2){
            if ((error >= 0) && (error || (iy > 0))){
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing
 
            error += delta_x;
            y1 += iy;
 
            img(x1,y1)->Red = 0;
			img(x1,y1)->Blue = 0;
			img(x1,y1)->Green = 0;
			img(x1,y1)->Alpha = 0;
        }
    }
}
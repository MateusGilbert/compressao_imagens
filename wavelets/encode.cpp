#include "missing_header.h"
#include "header.hpp"
#include <stdlib.h>

int** init_dd_img(int x, int y){
	int **dd_img = (int **) malloc(y*sizeof(int*));
	for (int i=0; i<y; i++)
		dd_img[i] = (int *) malloc(x*sizeof(int));

	return dd_img;
}

inline vector< string > split_str(string str, char split_at=' '){
	vector< string > strs;
	vector< size_t > pos;
	size_t p=0, last = str.find_last_of(split_at), p_ins=0;
	size_t len=str.length();
	while (++p < len)
		if (str[p] == split_at){
			strs.push_back(str.substr(p_ins,p-p_ins));
			p_ins=p+1;
		}
	strs.push_back(str.substr(last+1));

	return strs;
}


vector< string > get_codebooks(int lambda, vector< string > directories, string outfile){
	vector< string > codebooks;

	for (auto dir: directories){
		ifstream file(dir + "/" + outfile);
		string line, codebook;
		float D,R,best=1e6;
		getline(file,line);			//ignore header
		while(getline(file,line)){
			vector< string > entries = split_str(line,',');
			string aux = entries[0];
			D = atof(entries[1].c_str());
			R = atof(entries[2].c_str());
			if ((D + (float) lambda*R) < best){//implementar convex hull -- esse search está errado
				best = D + (float) lambda*R;
				codebook = aux;
			}
		}
		codebooks.push_back(codebook);
	}

	return codebooks;
}

int
main(int argc, char *argv[]){
	if (argc < NBANDS+2){//ajeitar
		cout<<"Usage: "<<argv[0]<<" -l [lambda] -d [codebook-directories] -f [files]"<<endl;
		return 1;
	}

	int lambda = stoi(argv[1]);
	int shift=2; //ajeitar e acrescentar switch
	vector< string > directories;
	while(shift < argc)
		directories.push_back(argv[shift++]);

	vector< string > codebooks = get_codebooks(lambda,directories);
	for (auto codebook: codebooks)
		cout<<codebook<<endl;

//	vect_list tr_vects;
//	for (string file : files){
//		int x=0,y=0;
//		int *im_array = op_pgm(x,y,file);
//		int **dd_img = im_to_ddot(im_array, x, y);
//		int **dd_out = init_dd_img(x,y);
//		int **dd_dec = init_dd_img(x,y);
//
//		double *sIMG[YIMG];
//		analysis(dd_img,dd_dec, sIMG, x, y);
//		int *d_img = ddot_to_im(dd_dec, x, y);
//		save_csv(d_img, x, y, file + "d.csv");
//
//		synthesis(sIMG, dd_out, x, y);
//		int *r_img = ddot_to_im(dd_out, x, y);
//		save_csv(r_img, x, y, file + ".csv");
//	}

	return 0;
}

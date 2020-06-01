#include <iostream>

#include <vector>

#include <cmath>

using namespace std;

constexpr double bias{-1.0};

const vector<vector<double>> Weights{ { -1, 1, -0.9, -0.9 }, { -0.6, 0.6, -0.1, -0.1 }, { -2.7, 0.1, -2.0, -2.0 } }; //Generated under supervised learning

struct Neuron;

typedef vector<Neuron> Layer;

struct Neuron{

	double out,gradient;

	vector<double> W;//Weights

	Neuron(const int inputs,bool bias) {

		for( int i = 0; i < inputs; i++ ) {

			W.push_back(0);

		}

		if(bias) {

			W.push_back(0);

		}

	}
	void SetOutput(const Layer &L) {

		double sum{0};

		for(int i = 0;i < L.size(); i++) {

			sum += L[i].out*W[i];

		}

		sum += W.back()*bias;

		out = tanh(sum);

	}

};

struct Net{

	vector<Layer> L;

	Net()=default;

	Net( const vector<int> &topology ) {

		for(int j = 0; j < topology.size(); j++) {

			L.push_back(Layer());

			for(int i = 0; i < topology[j]; i++) {

				L.back().push_back(Neuron(j == 0 ? 0 : topology[j - 1],j != 0));
			
			}

		}

	}

	void FeedForward(const vector<double> &I) {

		for(int i = 0; i < L[0].size(); i++) {

			L[ 0 ][ i ].out = I[i];

		}

		for(int i = 1; i < L.size(); i++) {

			for( Neuron &n : L[ i ] ) {

				n.SetOutput( L[ i - 1 ] );

			}

		}

	}

	vector<double> Get_Output() {

		vector<double> res;

		for(const Neuron &n : L.back()) {

			res.push_back(n.out);

		}

		return res;

	}

};

int main() {

    while ( true ) {

        string name1, name2;//In case you want to name the distances, eg  Home and Work

        int dist1, dist2;

        cin >> name1 >> dist1 >> name2 >> dist2;

        vector<int> topology{2, 2, 1};

        Net Brain(topology);

        int j=0;

        for(int k = 1; k < Brain.L.size(); k++) {

        	Layer &l=Brain.L[k];

        	for(Neuron &n : l) {

        		for(int i = 0; i < n.W.size(); i++) {

        			n.W[i]=Weights[j][i];
					
        		}

        		j++;

        	}

        }

        vector<double> Inputs{ dist1 / 100.0 , dist2 / 100.0 };

        Brain.FeedForward(Inputs);

        double result{ round( Brain.Get_Output()[0] ) };

        cout << ( result == 0 ? name1 : name2 ) << endl;

    }
    
}






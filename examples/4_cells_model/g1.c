#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define True 1

#define False 0

//Events


extern void readInput();

extern void writeOutput();
extern double x1; //inputs continuous
extern double xme; //inputs continuous

//Continuous variables and Outputs

double v_aggregate; //output continuous g
extern unsigned char VSP, VS;

// The magical g-function based on Mark Trew's derivation.
// For a given cell (called the "central" cell), this function 
// returns the aggregate voltage of its neighbouring cells.
double g(
		// Function parameters:

		// General cell parameters.
		double A_m, 				// Cell surface area to cell volume. Units of per millimeter.
		double C_m,					// Specific membrane capacitance. Units of microfarad per millimeter squared.

		// Parameters related to the central cell.
		double v_k_pre,				// Voltage of the central cell "k" at the previous time of "t - delta(t)". Units of millivolt.

		// Parameters related to the neighbouring cells.
		double d_ik[],				// Distance between the neighbouring cells "i" and the central cell "k". Units of millimeter.
		double gamma_ik[],			// Surface/cross-sectional area between neighbouring cells "i" and the central cell "k". Units of millimeter squared
		double sigma_ik[],			// Electrical conductivity (not isotropic or homogeneous) between neighbouring cells "i" and the central cell "k". Units of per millisiemens per millimeter squared.
		double v_i_pre[],			// Voltage of neighbouring cells "i" at the previous time of "t - delta(t)". Units of millivolt.
		int neighbourCount			// Number of neighbouring cells.
) {
	// Sum up the potential differences between the neighbouring cells "i" and the central cell "k".
	// The sum is proportional to the surface/cross-sectional area between the central cell and each of its neighbours.
	v_aggregate = 0;
	int i;
	for (i = 0; i < neighbourCount; ++i) {
		v_aggregate += (gamma_ik[i]*sigma_ik[i] * (v_i_pre[i] - v_k_pre)) / (A_m*C_m * d_ik[i]);
	}

	// Return the aggregate voltage.
	return v_aggregate;
}


int main(int argc, char **argv) {
	// Test the g function using three neighbouring cells.

	// General cell parameters.
	double A_m = 200; 			// Cell surface area to cell volume. Units of per millimeter.
	double C_m = 0.01;			// Specific membrane capacitance. Units of microfarad per millimeter squared.

	// Parameters related to the central cell.
	double v_k_pre = -50;		// Votlage of the central cell "k" at the previous time of "t - delta(t)". Units of millivolt.

	// Parameters related to the neighbouring cells.
	double d_ik[] = {1, 2, 1.5};			// Distance between the neighbouring cells "i" and the central cell "k". Units of millimeters.
	double gamma_ik[] = {0.1, 0.2, 0.1};	// Surface/cross-sectional area between neighbouring cells "i" and the central cell "k". Units of millimeter squared
	double sigma_ik[] = {0.1, 0.2, 0.1};	// Electrical conductivity (not isotropic or homogeneous) between neighbouring cells "i" and the central cell "k". Units of per millisiemens per millimeter squared.
	double v_i_pre[] = {-10};		// Voltage of neighbouring cells "i" at the previous time of "t - delta(t)". Units of millivolt.
	int neighbourCount = 1;					// Number of neighbouring cells.
	int flag=0;
	
	while(True) {
		readInput();
		v_i_pre[0]=x1;
		
		if(flag==1){
			v_k_pre = xme;
		}
		// Compute the aggregate voltage.
		v_aggregate = g(A_m, C_m, v_k_pre, d_ik, gamma_ik, sigma_ik, v_i_pre, neighbourCount);
		
		printf("Aggregated voltage is %f mV\n", v_aggregate);
		writeOutput();
		flag=1;
	}

	return 0;
}


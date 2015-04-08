#include <iostream>
#include "./Eigen/Dense"

using namespace Eigen;
using namespace std;

int main()
{
	MatrixXd A(3, 3);
	A(0, 0) = 0;
	A(0, 1) = 1;
	A(0, 2) = 0;
	A(1, 0) = 1;
	A(1, 1) = 0;
	A(1, 2) = 1;
	A(2, 0) = 0;
	A(2, 1) = 1;
	A(2, 2) = 0;

	cout << "Here is a random 3x3 matrix, A:" << endl << A << endl << endl;
	EigenSolver<MatrixXd> es(A);
	cout << "The eigenvalues of A are:" << endl << es.eigenvalues() << endl;
	cout << "The matrix of eigenvectors, V, is:" << endl << es.eigenvectors() << endl << endl;
	complex<double> lambda = es.eigenvalues()[2];
	cout << "Consider the first eigenvalue, lambda = " << lambda << endl;
	VectorXcd v = es.eigenvectors().col(2);
	cout << "" <<endl << v.data() <<endl;
//	cout << "If v is the corresponding eigenvector, then lambda * v = " << endl << lambda * v << endl;
//	cout << "... and A * v = " << endl << A.cast<complex<double> >() * v << endl << endl;
}

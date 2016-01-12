
#include <algorithm>
#include <cmath>
#include <complex>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef complex<double> ComplexD;
typedef vector<ComplexD> ComplexVectorD;

const int dig_base          = 10;
const int base              = 10;
const int dig_size          = 1;
const size_t max_naive_mult = 0;


ComplexVectorD FastFourierTransform(const ComplexVectorD &coeffs) {
    int n = coeffs.size();
    if (n == 1) {
        return ComplexVectorD(1, coeffs[0]);
    }

    ComplexVectorD w(n);
    for (int i = 0; i < n; i++) {
        double alpha = 2 * M_PI * i / n;
        w[i] = ComplexD(cos(alpha), sin(alpha));
    }

    ComplexVectorD A(n / 2), B(n / 2);
    for (int i = 0; i < n / 2; i++) {
        A[i] = coeffs[i * 2];
        B[i] = coeffs[i * 2 + 1];
    }

    ComplexVectorD Av = FastFourierTransform(A);
    ComplexVectorD Bv = FastFourierTransform(B);
    ComplexVectorD res(n);

    for (int i = 0; i < n; i++) {
        res[i] = Av[i % (n / 2)] + w[i] * Bv[i % (n / 2)];
    }
    return res;
}

ComplexVectorD InverseFourierTransform(const ComplexVectorD& as) {
    ComplexVectorD res = FastFourierTransform(as);
    for (int i=0; i<(int)res.size(); i++) {
        res[i] /= as.size();
    }
    reverse(res.begin() + 1, res.end());
    return res;
}

ComplexVectorD PolynomialProduct(
    const ComplexVectorD& polynomial1,
    const ComplexVectorD& polynomial2
) {
    ComplexVectorD helper1 = polynomial1;
    helper1.resize(polynomial1.size() * 2);
    ComplexVectorD helper2 = polynomial2;
    helper2.resize(polynomial2.size() * 2);

    ComplexVectorD p1_vals = FastFourierTransform(helper1);
    ComplexVectorD p2_vals = FastFourierTransform(helper2);
    ComplexVectorD res_vals(p1_vals.size());
    for (int i = 0; i < p1_vals.size(); i++) {
        res_vals[i] = p1_vals[i] * p2_vals[i];
    }
    return InverseFourierTransform(res_vals);
}


vector<int> GetNumber(istream& is) {
    string      string_num;
    vector<int> vnum;

    unsigned int dig    = 1;
    int n               = 0;

    is >> string_num;

    for (auto it = string_num.crbegin(); it != string_num.crend(); it++) {
        n += (*it - '0') * dig;
        dig *= dig_base;

        if (dig == base) {
            vnum.push_back(n);
            n   = 0;
            dig = 1;
        }
    }
    if (n != 0) {
        vnum.push_back(n);
    }
    return vnum;
}

void ExtendVec(vector<int>& v, size_t len) {
    while (len & (len - 1)) {
        len++;
    }
    v.resize(len);
}

void Finalize(vector<int>& res) {
    for (auto i = 0; i < res.size(); i++) {
        res[i + 1] += res[i] / base;
        res[i] %= base;
    }
}

void PrintRes(const vector<int>& v, ostream& os) {
    auto it = v.crbegin();

    // Passing leading zeroes
    while (!*it) {
        it++;
    }

    while (it != v.crend()) {
        os << *it++;
    }
    os << endl;
}

vector<int> NaiveMultiplication(vector<int>& x, vector<int>& y) {
    int len = max(x.size(), y.size());
    x.resize(len);
    y.resize(len);
    vector<int> res(len * 2);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            res[i + j] += x[i] * y[j];
        }
    }
    Finalize(res);
    return res;
}

int GetLesserPowerOf2(int n) {
    double log2_of_n = log2(n);
    double frac, integer;
    frac = modf(log2_of_n, &integer);
    if (frac > 0) {
        integer++;
    }
    return pow(2, integer);
}

vector<int> SchonhageStrassenMultiplication(vector<int>& x, vector<int>& y) {
    int bigger = max(x.size(), y.size());
    x.resize(bigger);
    y.resize(bigger);
    int new_size = GetLesserPowerOf2(bigger);
    ComplexVectorD complex_x(new_size);
    ComplexVectorD complex_y(new_size);
    for (size_t i = 0; i < x.size(); i++) {
        complex_x[i] = ComplexD(x[i], 0);
        complex_y[i] = ComplexD(y[i], 0);
    }
    ComplexVectorD complex_res = PolynomialProduct(complex_x, complex_y);
    vector<int> res(complex_res.size());
    for (size_t i = 0; i < complex_res.size(); i++) {
        double subres = round(complex_res[i].real());
        res[i] = static_cast<int>(subres);
    }
    Finalize(res);
    return res;
}

namespace naive {
const string line   = "------------------------------\n";
const string header = "Naive Multiplication Algorithm\n";

void RunNaiveMultiplication(int iterations, istream& in, ostream& out) {
    clock_t global_time1 = clock();
    for (int i = 0; i < iterations; i++) {
        vector<int> num1    = GetNumber(in);
        vector<int> num2    = GetNumber(in);
        clock_t t1          = clock();
        auto res            = NaiveMultiplication(num1, num2);
        clock_t t2          = clock();
        out << i + 1 << ". ";
        PrintRes(res, out);
        out << "Time elapsed: " << 1000.0 * (t2-t1) / CLOCKS_PER_SEC << " ms\n";
        out << endl;
    }
    clock_t global_time2 = clock();
    out << "Overall time elapsed: " << 1000.0 * (global_time2 -global_time1) / CLOCKS_PER_SEC << " ms\n";
}

void TestTrivialCases(ostream& out) {
    ifstream in("trivial.in");
    int n;
    in >> n;
    out << endl << line << header << "Testing on trivial cases\n" << line;
    RunNaiveMultiplication(n, in, out);
    out << line;
}

void TestHundredsCases(ostream& out) {
    out << endl << line << header;
    out << "Testing on numbers with \n100 to 1000 decimal digits\n" << line;
    ifstream in("100.in");
    int n;
    in >> n;
    RunNaiveMultiplication(n, in, out);
    out << line;
}

void TestThousandsCases(ostream& out) {
    out << endl << line << header;
    out << "Testing on numbers with \n1K to 10K decimal digits\n" << line;
    ifstream in("1K.in");
    int n;
    in >> n;
    RunNaiveMultiplication(n, in, out);
    out << line;
}

void TestTensOfThousandsCases(ostream& out) {
    out << endl << line << header;
    out << "Testing on numbers with \n10K to 100K decimal digits\n" << line;
    ifstream in("10K.in");
    int n;
    in >> n;
    RunNaiveMultiplication(n, in, out);
    out << line;
}


} // naive

namespace schonhage_strassen {
const string line   = "------------------------------\n";
const string header = "Schonhage Stassen Algorithm\n";
void RunSchonhageStrassenMultiplication(int iterations, istream& in, ostream& out) {
    clock_t global_time1 = clock();
    for (int i = 0; i < iterations; i++) {
        vector<int> num1    = GetNumber(in);
        vector<int> num2    = GetNumber(in);
        clock_t t1          = clock();
        auto res            = SchonhageStrassenMultiplication(num1, num2);
        clock_t t2          = clock();
        out << i + 1 << ". ";
        PrintRes(res, out);
        out << "Time elapsed: " << 1000.0 * (t2-t1) / CLOCKS_PER_SEC << " ms\n";
        out << endl;
    }
    clock_t global_time2 = clock();
    out << "Overall time elapsed: " << 1000.0 * (global_time2 -global_time1) / CLOCKS_PER_SEC << " ms\n";
}

void TestTrivialCases(ostream& out) {
    ifstream in("trivial.in");
    int n;
    in >> n;
    out << endl << line << header << "Testing on trivial cases\n" << line;
    RunSchonhageStrassenMultiplication(n, in, out);
    out << line;
}

void TestHundredsCases(ostream& out) {
    out << endl << line << header;
    out << "Testing on numbers with \n100 to 1000 decimal digits\n" << line;
    ifstream in("100.in");
    int n;
    in >> n;
    RunSchonhageStrassenMultiplication(n, in, out);
    out << line;
}

void TestThousandsCases(ostream& out) {
    out << endl << line << header;
    out << "Testing on numbers with \n1K to 10K decimal digits\n" << line;
    ifstream in("1K.in");
    int n;
    in >> n;
    RunSchonhageStrassenMultiplication(n, in, out);
    out << line;
}

void TestTensOfThousandsCases(ostream& out) {
    out << endl << line << header;
    out << "Testing on numbers with \n10K to 100K decimal digits\n" << line;
    ifstream in("10K.in");
    int n;
    in >> n;
    RunSchonhageStrassenMultiplication(n, in, out);
    out << line;
}

} // namespace schonhage_strassen


int main(int argc, char const *argv[]){
    ofstream ss("out_ss-O3.txt");
    schonhage_strassen::TestTrivialCases(ss);
    schonhage_strassen::TestHundredsCases(ss);
    schonhage_strassen::TestThousandsCases(ss);
    schonhage_strassen::TestTensOfThousandsCases(ss);
    ofstream naive("out_naive-O3.txt");
    naive::TestTrivialCases(naive);
    naive::TestHundredsCases(naive);
    naive::TestThousandsCases(naive);
    naive::TestTensOfThousandsCases(naive);
    return 0;
}

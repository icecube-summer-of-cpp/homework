# include "quiz.hxx"

void print_matrix_header(std::ifstream& file)
{
     std::cout << std::cin << file << std::endl;
}

int main(int argc, char* argv[])
{
    std::cout << "Reading file " << argv[1] << std::endl;
    std::ifstream matrix_file(argv[1]);
    print_matrix_header(matrix_file);
    return 0;
}
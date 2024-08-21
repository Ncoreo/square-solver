#include <stdio.h>
#include <math.h>

int compare_doubles(double a, double b, double eps);

int solve(double a, double b, double c, double* x1, double* x2);
int solve_quadratic(double a, double b, double c, double* x1, double* x2);
int solve_linear(double b, double c, double* x);

int input(int n, double* pointers[]);
int getnumber(double* n);

void output(int nroots, double x1, double x2);

int test(int n, double a, double b, double c, double x1, double x2, int roots_exp, double x1_exp, double x2_exp);

int main()
{
    double a = 0,b = 0,c = 0,x1 = 0,x2 = 0;
    test(1, 1, 2, -3, x1, x2, 2, 1, -3); //Successful
    test(2, 2, 7, -9, x1, x2, 1, 5, 0); //Wrong
    double* p[3]={&a,&b,&c};
    printf("Enter a,b,c:\n");
    int error = input(3,p);
    while(error)
    {
        printf("Try again:\n");
        while(getchar()!='\n');
        error = input(3,p);
    }
    int roots = solve(a, b, c, &x1, &x2);
    output(roots, x1, x2);

    return 0;
}

enum roots
{
    INFROOTS = -1,
    NOROOTS = 0,
    ONEROOT = 1,
    TWOROOTS = 2
};

int compare_doubles(double a, double b, double eps)
{
    return fabs(a-b) > eps ? 0 : 1;
}

int solve(double a, double b, double c, double* x1, double* x2)
{
    if(!compare_doubles(a,(double)0,0.000001)) return solve_quadratic(a,b,c,x1,x2);
    return solve_linear(b,c,x1);
}

int solve_quadratic(double a, double b, double c, double* x1, double* x2)
{
    double d = b*b - 4*a*c;
        if(d >= 0)
        {
            *x1 = (-b+sqrt(d))/(2*a);
            *x2 = (-b-sqrt(d))/(2*a);
            return TWOROOTS;
        }
        else if(d==0) // enum
        {
            *x1 = -b/(2*a);
            return ONEROOT;
        }
        else return NOROOTS;
}

int solve_linear(double a, double b, double* x)
{
    if(a==0)
    {
        if(b==0) return INFROOTS;
        else return NOROOTS;
    }
    else
    {
        *x=-b/a;
        return ONEROOT;
    }

}

int getnumber(double* n)
{
    scanf("%lf", n);
    int next = getchar();
    if(next=='\n' || next==' ') return 0;
    return -1;
}

int input(int n, double* pointers[])
{
    for(int i=0;i<n;i++)
    {
        int error = getnumber(pointers[i]);
        if(error)
        {
            printf("Error on reading %d number\n",i + 1);
            return -1;
        }
    }
    return 0;
}

void output(int nroots, double x1, double x2)
{
    switch (nroots)
    {
    case INFROOTS:
        printf("Infinity roots\n");
        break;
    case NOROOTS:
        printf("No roots\n");
        break;
    case ONEROOT:
        printf("One root: %lf\n", x1);
        break;
    case TWOROOTS:
        printf("Two roots: %lf and %lf\n", x1, x2);
        break;
    default:
        break;
    }
}

int test(int n, double a, double b, double c, double x1, double x2, int nroots_exp, double x1_exp, double x2_exp)
{
    int nroots = solve(a, b, c, &x1, &x2);
    if(nroots != nroots_exp || (x1 != x1_exp && x1 != x2_exp) || (x2 != x2_exp && x2 != x1_exp))
    {
        printf(
            "Failed on test %d: a = %lf, b = %lf, c = %lf\n"
            "Expected: nRoots = %d, x1 = %lf, x2 = %lf\n"
            "Result: nRoots = %d, x1 = %lf, x2 = %lf\n",
            n, a, b, c, nroots_exp, x1_exp, x2_exp, nroots, x1, x2
        );
        return -1;
    }
    return 0;

}
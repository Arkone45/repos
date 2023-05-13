using System.Numerics;
using System.Runtime.InteropServices;
using System.Security.Cryptography.X509Certificates;
using System.Text;
internal class Program
{
    public class Matrtix
    {
        public int[,] A;
        public void read()
        {
            int n = Convert.ToInt32(Console.ReadLine());
            A = new int[n, n];
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    A[i, j] = Convert.ToInt32(Console.ReadLine());
                }
            }
        }
        public void print()
        {
            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    Console.Write(A[i, j] + " ");
                }
                Console.WriteLine();
            }
        }
    }
    public class Umatrix : Matrtix
    {
        public bool MoreNeg()
        {
            int n = 0;
            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    if (A[i,j] < 0)
                        n --;
                    else if (A[i,j] > 0)
                        n ++;
                }
            }
            if (n < 0)
                return true;
            else
                return false;
        }
        public int avr()
        {
            int n = 0;
            int s = 0;
            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    s += A[i, j];
                    n ++;
                }
            }
            s /= n;
            return s;
        }
        public void adder()
        {
            int s = avr();
            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    A[i, j] += s;
                }
            }
        }
    }
    private static void Main(string[] args)
    {
        Umatrix X = new Umatrix();
        X.read();
        X.print();
        if (X.MoreNeg())
        {
            X.adder();
        }
        X.print();
    }
}
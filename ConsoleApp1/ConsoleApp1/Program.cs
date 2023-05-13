using System.Runtime.InteropServices;
using System.Text;
internal class Program
{
    static bool IsNeg(int[,] X)
    {
        for (int i = 0; i < X.GetLength(0); i++)
            for (int j = 0; j < i; j++)
                if (X[i, j] < 0)
                    return false;
        return true;
    }
    static int[,] Mult(int[,] X)
    {
        for (int i = 0; i < X.GetLength(0); i++)
        {
            for (int j = 0; j < X.GetLength(1); j++)
            {
                X[i, j] *= X[i, i];
            }
        }
        return X;
    }
    static void Printer(int[,] X)
    {
        Console.WriteLine("Матрица:");
        for (int i = 0; i < X.GetLength(0); i++)
        {
            for (int j = 0; j < X.GetLength(1); j++)
            {
                Console.Write(X[i, j]);
                Console.Write(' ');
            }
            Console.WriteLine();
        }
    }
    static void Reader(int[,] X)
    {
        for (int i = 0; i < X.GetLength(0); i++)
            for (int j = 0; j < X.GetLength(1); j++)
                X[i, j] = Convert.ToInt32(Console.ReadLine());
    }
    private static void Main(string[] args)
    {
        Console.OutputEncoding = Encoding.UTF8;
        int[,] A;
        int n;
        Console.WriteLine("Размер: ");
        n = Convert.ToInt32(Console.ReadLine());
        A = new int[n, n];
        Reader(A);
        Printer(A);  
        if (IsNeg(A))
            A = Mult(A);
        Printer(A);
    }
}
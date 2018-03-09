import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Random;

public class Lab1 {
    static double S = 1.36;
    static int N = 50;
    static int a0 = 12167;
    static int b = 12167;
    static int L = 10;
    static double M = Math.pow(2, 31);

    static double sequenceElement = a0;

    public static double[] MKM(){ //метод конгруэнтного моделирования
        double[] array = new double[N];

        double el1;

        for(int i = 0; i < N; i++)
        {
            el1 = (sequenceElement * b) % M;
            array[i] = el1/M;
            sequenceElement = el1;
        }
        return array;
    }

    static int K = 48;
    static double[] V = new double[K];

    public static double[] MMM(double[] B, double[] C){ // метод Маклорена-Марсальи
        double[] A = new double[N];
        for(int i = 0; i < K; i++)
            V[i] = B[i];

        for(int i = 0; i < N; i++)
        {
            int s = (int)(C[i] * K);
            A[i] = V[s];
            V[s] = B[(K + i) % N];
        }

        return A;
    }

    public static boolean kolmogorov_criterion(double[] X){ //L - число разбений интервала (0, 1) | N - обьем выборки{
       // m׳j = n · fj · ΔL, (5.1)
        // где n - объем выборки; fj - плотность распределения вероятностей, вычисленная по
        // теоретическому уравнению плотности распределения принятого закона для середины каждого интервала.
        //X2 = sum (mj - m'j)/ m'j   **( 0 < j < L)**
        Arrays.sort(X);
        double sup = 0;
        double temp;

        for(int i = 0; i < N; i++)
        {
            temp = Math.abs(X[i] - (double)i / N);
            if(sup < temp)
                sup = temp;
        }

        System.out.println("Вычисленное отклонение : " + (sup * Math.sqrt(N)));
        System.out.println("Табличное отклонение : " + S);

        return (Math.sqrt(N) * sup) < S;
    }

    public static boolean pirson_criterion(double[] X) {
        double hi_table = 18.3;
        int[] hits = new int[L];

        for (int i = 0; i < N; i++)
            hits[(int) (X[i] * L)]++;

        double hi = 0;
        double expected = 1.0 / L;

        for (int i = 0; i < L; i++)
            hi += Math.pow((hits[i] * 1.0 / N) - expected, 2) / expected;

        hi *= N;

        System.out.println("\n\n*******************\nГистограмма: ");
        for(int i = 0; i < L; i++)
        {
            System.out.print(String.format("%.2f", (double)(i + 1) / L) + " ") ;
            System.out.println(hits[i]);
            System.out.println();
        }
        System.out.println("*******************");

        System.out.println("Вычисленное X^2: " + hi);
        System.out.println("Табличное X^2: " + hi_table);

        return hi_table > hi;
    }

    public static void main(String[] args) throws IOException {

        double[] array = MKM();
        double[] B = new double[N];
        double[] C = new double[N];
        Random rand = new Random();

        PrintWriter out1 = new PrintWriter("MKM.txt");
        PrintWriter out2 = new PrintWriter("MacMar.txt");
        for(int i = 0; i < N; i++) {
            out1.println(Double.toString(array[i]));
            B[i] = array[i];
            C[i] = rand.nextDouble()/Double.MAX_VALUE;
        }

        double[] A = MMM(B, C);
        for(int i = 0; i < N; i++) {
            out2.println(Double.toString(A[i]));
        }

        System.out.println("Критерий Пирсона для последовательности БСВ, построенной с помощью мультипликативного конгруэтного метода: ");
        if(pirson_criterion(array))
            System.out.println("Критерий Пирсона выполняется.");
        else
            System.out.println("Критерий Пирсона не выполняется.");

        System.out.println("Критерий Пирсона для последовательности БСВ, построенной с помощью метода Макларена-Марсальи: ");
        if(pirson_criterion(A))
            System.out.println("Критерий Пирсона выполняется.");
        else
            System.out.println("Критерий Пирсона не выполняется.");

        System.out.println("Критерий Колмогорова для последовательности БСВ, построенной с помощью мультипликативного конгруэнтного метода: ");
        if(kolmogorov_criterion(array))
            System.out.println("Критерий Колмогорова выполняется.");
        else
            System.out.println("Критерий Колмогорова не выполняется.");

        System.out.println("Критерий Колмогорова для последовательности БСВ, построенной с помощью метода Макларена-Марсальи: ");
        if(kolmogorov_criterion(A))
            System.out.println("Критерий Колмогорова выполняется.");
        else
            System.out.println("Критерий Колмогорова не выполняется.");

        out1.close();
        out2.close();
    }
}

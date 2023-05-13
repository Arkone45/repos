namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        public int[,] A;
        public Form1()
        {
            InitializeComponent();
        }
        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
        private void Form1_Load(object sender, EventArgs e)
        {
            dataGridView1.RowCount = dataGridView1.ColumnCount = 1;
        }
        private void dataGridView1_EditingControlShowing(object sender, DataGridViewEditingControlShowingEventArgs e)
        {
            TextBox tb = (TextBox)e.Control;
            tb.KeyPress += new KeyPressEventHandler(tb_KeyPress);
        }
        void tb_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!(Char.IsDigit(e.KeyChar)) && !((e.KeyChar == '-')))
            {
                if (e.KeyChar != (char)Keys.Back)
                {
                    e.Handled = true;
                }
            }
        }
        private void button2_Click(object sender, EventArgs e)
        {
            dataGridView1.Columns.Add("", "");
            dataGridView1.Rows.Add("", "");
        }
        private void button3_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Remove(dataGridView1.Rows[dataGridView1.Rows.GetLastRow(0)]);
            dataGridView1.Columns.Remove(dataGridView1.Columns[dataGridView1.Columns.GetColumnCount(0)-1]);
        }
        private bool IsNeg(int[,] X)
        {
            for (int i = 0; i < X.GetLength(0); i++)
                for (int j = 0; j < i; j++)
                    if (X[i, j] < 0)
                        return false;
            return true;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            A = new int[dataGridView1.RowCount, dataGridView1.ColumnCount];
            for (int i = 0; i < A.GetLength(0); i++)
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    if ((dataGridView1[i, j].Value == null)||(dataGridView1[i, j].Value.ToString() == ""))
                        A[i, j] = 0;
                    else
                        A[i, j] = Convert.ToInt32(dataGridView1[i, j].Value);
                }
            if (IsNeg(A))
            {
                for (int i = 0; i < A.GetLength(1); i++)
                {
                    for (int j = 0; j < A.GetLength(0); j++)
                    {
                        A[j, i] *= A[i, i];
                    }
                }
            }
            for (int i = 0; i < A.GetLength(0); i++)
                for (int j = 0; j < A.GetLength(1); j++)
                    dataGridView1[i, j].Value = A[i, j];
        }
    }
}
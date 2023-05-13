using System.Net.Http.Headers;
using System.Windows.Forms;

namespace ПИ_Лаб_6
{
    public struct LItem
    {
        public string Firm;
        public string Subdiv;
        public int Inc;
    }
    public partial class MainForm : Form
    {
        public List<LItem> main_list = new List<LItem>();
        public MainForm()
        {
            InitializeComponent();
        }
        public void ListTransfer(List<LItem> sendr, List<LItem> recip)
        {
            recip.Clear();
            for (int i = 0; i < sendr.Count; i++)
                recip.Add(sendr[i]);
        }
        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
        private void EditButton_Click(object sender, EventArgs e)
        {
            Enabled = false;
            Visible = false;
            EditForm editForm = new EditForm(this);
            ListTransfer(main_list, editForm.edit_list);
            editForm.ShowDialog();
            editForm.GridUpdate(MainList, main_list);
            Visible = true;
            Enabled = true;
        }
        private void SearchButton_Click(object sender, EventArgs e)
        {
            Enabled = false;
            Visible = false;
            AnalyzeForm analyzeForm = new AnalyzeForm(main_list);
            analyzeForm.ShowDialog();
            Visible = true;
            Enabled = true;
        }
    }
}
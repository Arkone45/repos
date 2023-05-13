using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ПИ_Лаб_6
{
    public partial class AnalyzeForm : Form
    {
        private List<LItem> analyze_list;
        public AnalyzeForm(List<LItem> list)
        {
            InitializeComponent();
            analyze_list = list;
        }
        private void FirmDropList_SelectedIndexChanged(object sender, EventArgs e)
        {
            int num = 0;
            IEnumerable<LItem> incomes = from item in analyze_list where item.Firm.Equals(FirmDropList.Items[FirmDropList.SelectedIndex]) select item;
            foreach (LItem item in incomes)
            {
                if (item.Inc > 0)
                    num += 1;
                else
                    num -= 1;
            }
            if (num > 0)
                label1.Text = "В этой фирме преобладают прибыльные подраздееления.";
            else
                label1.Text = "В этой фирме преобладают убыточные подраздееления.";
        }
        private void AnalyzeForm_Load(object sender, EventArgs e)
        {
            for (int i = 0; i < analyze_list.Count; i++)
                if (!FirmDropList.Items.Contains(analyze_list[i].Firm))
                    FirmDropList.Items.Add(analyze_list[i].Firm);
        }
    }
}

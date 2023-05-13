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
    public partial class EditForm : Form
    {
        MainForm form;
        public List<LItem> edit_list = new List<LItem>();
        private static void ItemMove(List<LItem> list, int indx, bool up)
        {
            LItem elem = list[indx];
            list.RemoveAt(indx);
            if (up)
                list.Insert(indx - 1, elem);
            else
                list.Insert(indx + 1, elem);
        }
        public void GridUpdate(DataGridView grid, List<LItem> list)
        {
            grid.RowCount = list.Count;
            for (int i = 0; i < list.Count; i++)
            {
                grid.Rows[i].HeaderCell.Value = i.ToString();
                grid.Rows[i].Cells[0].Value = list[i].Firm;
                grid.Rows[i].Cells[1].Value = list[i].Subdiv;
                grid.Rows[i].Cells[2].Value = list[i].Inc.ToString();
            }
        }
        public EditForm(MainForm par)
        {
            InitializeComponent();
            form = par;    
        }
        private void EditForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            form.ListTransfer(edit_list, form.main_list);
        }
        private void AddButton_Click(object sender, EventArgs e)
        {
            LItem item;
            item.Firm = "Новая фирма";
            item.Subdiv = "Новое подразделение " + "(" + edit_list.Count.ToString() + ")";
            item.Inc = 0;
            edit_list.Add(item);
            GridUpdate(EditList, edit_list);
            if (!DeleteButton.Enabled)
                DeleteButton.Enabled = true;
            if (EditList.CurrentRow.Index != 0)
                MoveUpButton.Enabled = true;
            else
                MoveUpButton.Enabled = false;
            if (EditList.CurrentRow.Index != EditList.RowCount - 1)
                MoveDownButton.Enabled = true;
            else
                MoveDownButton.Enabled = false;
        }
        private void DeleteButton_Click(object sender, EventArgs e)
        {
            if (EditList.RowCount > 0)
                edit_list.RemoveAt(edit_list.Count - 1);
            GridUpdate(EditList, edit_list);
            if (edit_list.Count == 1)
                DeleteButton.Enabled = false;
            if (EditList.CurrentRow.Index != 0)
                MoveUpButton.Enabled = true;
            else
                MoveUpButton.Enabled = false;
            if (EditList.CurrentRow.Index != EditList.RowCount - 1)
                MoveDownButton.Enabled = true;
            else
                MoveDownButton.Enabled = false;
        }
        private void EditForm_Load(object sender, EventArgs e)
        {
            GridUpdate(EditList, edit_list);
            EditList.TopLeftHeaderCell.Value = "№";
            if (EditList.RowCount == 0)
                DeleteButton.Enabled = false;
            MoveUpButton.Enabled = false;
            if (EditList.RowCount < 2)
                MoveDownButton.Enabled = false;
            else
                MoveDownButton.Enabled = true;
        }
        private void MoveUpButton_Click(object sender, EventArgs e)
        {
            ItemMove(edit_list, EditList.CurrentRow.Index, true);
            GridUpdate(EditList, edit_list);
            EditList.CurrentCell = EditList.Rows[EditList.CurrentRow.Index - 1].Cells[0];
            EditList.CurrentRow.Selected = true;
        }
        private void MoveDownButton_Click(object sender, EventArgs e)
        {
            ItemMove(edit_list, EditList.CurrentRow.Index, false);
            GridUpdate(EditList, edit_list);
            EditList.CurrentCell = EditList.Rows[EditList.CurrentRow.Index + 1].Cells[0];
            EditList.CurrentRow.Selected = true;
        }
        private void EditList_SelectionChanged(object sender, EventArgs e)
        {
            EditList.SelectionChanged -= new System.EventHandler(EditList_SelectionChanged);
            EditList.ClearSelection();
            EditList.CurrentRow.Selected = true;
            if (EditList.CurrentRow.Index != 0)
                MoveUpButton.Enabled = true;
            else
                MoveUpButton.Enabled=false;
            if (EditList.CurrentRow.Index != EditList.RowCount - 1)
                MoveDownButton.Enabled = true;
            else
                MoveDownButton.Enabled = false;
            EditList.SelectionChanged += new System.EventHandler(EditList_SelectionChanged);
        }

        private void EditList_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            LItem elem;
            if (e.RowIndex > -1)
            {
                elem = edit_list[e.RowIndex];
                switch (e.ColumnIndex)
                {
                    case 0:
                        elem.Firm = EditList.Rows[e.RowIndex].Cells[0].Value.ToString();
                        break;
                    case 1:
                        elem.Subdiv = EditList.Rows[e.RowIndex].Cells[1].Value.ToString();
                        break;
                    case 2:
                        elem.Inc = Convert.ToInt32(EditList.Rows[e.RowIndex].Cells[2].Value);
                        break;
                    default:
                        break;
                }
                edit_list[e.RowIndex] = elem;
            }
        }
    }
}

namespace ПИ_Лаб_6
{
    partial class AnalyzeForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.FirmDropList = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // FirmDropList
            // 
            this.FirmDropList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FirmDropList.DropDownWidth = 250;
            this.FirmDropList.FormattingEnabled = true;
            this.FirmDropList.Location = new System.Drawing.Point(12, 12);
            this.FirmDropList.Name = "FirmDropList";
            this.FirmDropList.Size = new System.Drawing.Size(222, 28);
            this.FirmDropList.TabIndex = 0;
            this.FirmDropList.SelectedIndexChanged += new System.EventHandler(this.FirmDropList_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(265, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(327, 192);
            this.label1.TabIndex = 1;
            // 
            // AnalyzeForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(604, 213);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.FirmDropList);
            this.Name = "AnalyzeForm";
            this.Text = "Анализировать";
            this.Load += new System.EventHandler(this.AnalyzeForm_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private ComboBox FirmDropList;
        private Label label1;
    }
}
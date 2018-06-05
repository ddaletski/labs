namespace LabApp
{
    partial class FormCondition
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
            this.cbOperation = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tbGroup = new System.Windows.Forms.TextBox();
            this.btnClose = new System.Windows.Forms.Button();
            this.rtbCollection = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // cbOperation
            // 
            this.cbOperation.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbOperation.Items.AddRange(new object[] {
            "<",
            "<=",
            "==",
            ">=",
            ">"});
            this.cbOperation.Location = new System.Drawing.Point(17, 38);
            this.cbOperation.Name = "cbOperation";
            this.cbOperation.Size = new System.Drawing.Size(121, 21);
            this.cbOperation.TabIndex = 0;
            this.cbOperation.SelectedIndexChanged += new System.EventHandler(this.cbOperation_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(119, 20);
            this.label1.TabIndex = 1;
            this.label1.Text = "Номер группы ";
            // 
            // tbGroup
            // 
            this.tbGroup.Location = new System.Drawing.Point(17, 65);
            this.tbGroup.Name = "tbGroup";
            this.tbGroup.Size = new System.Drawing.Size(121, 20);
            this.tbGroup.TabIndex = 2;
            this.tbGroup.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            this.tbGroup.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tb_KeyPress);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(22, 91);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(110, 40);
            this.btnClose.TabIndex = 3;
            this.btnClose.Text = "Отменить";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // rtbCollection
            // 
            this.rtbCollection.Location = new System.Drawing.Point(144, 15);
            this.rtbCollection.Name = "rtbCollection";
            this.rtbCollection.Size = new System.Drawing.Size(184, 178);
            this.rtbCollection.TabIndex = 5;
            this.rtbCollection.Text = "";
            // 
            // FormCondition
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(340, 205);
            this.Controls.Add(this.rtbCollection);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.tbGroup);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cbOperation);
            this.Name = "FormCondition";
            this.Text = "FormCondition";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cbOperation;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbGroup;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.RichTextBox rtbCollection;
    }
}
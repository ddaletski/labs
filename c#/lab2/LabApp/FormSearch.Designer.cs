namespace LabApp
{
    partial class FormSearch
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
            this.groupBox = new System.Windows.Forms.GroupBox();
            this.rbGrade = new System.Windows.Forms.RadioButton();
            this.rbGroup = new System.Windows.Forms.RadioButton();
            this.rbFullname = new System.Windows.Forms.RadioButton();
            this.label1 = new System.Windows.Forms.Label();
            this.tbFullname = new System.Windows.Forms.TextBox();
            this.tbGroup = new System.Windows.Forms.TextBox();
            this.tbGrade = new System.Windows.Forms.TextBox();
            this.btnClose = new System.Windows.Forms.Button();
            this.rtbCollection = new System.Windows.Forms.RichTextBox();
            this.groupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox
            // 
            this.groupBox.Controls.Add(this.rbGrade);
            this.groupBox.Controls.Add(this.rbGroup);
            this.groupBox.Controls.Add(this.rbFullname);
            this.groupBox.Location = new System.Drawing.Point(12, 12);
            this.groupBox.Name = "groupBox";
            this.groupBox.Size = new System.Drawing.Size(264, 50);
            this.groupBox.TabIndex = 10;
            this.groupBox.TabStop = false;
            this.groupBox.Text = "Поиск";
            // 
            // rbGrade
            // 
            this.rbGrade.AutoSize = true;
            this.rbGrade.Location = new System.Drawing.Point(166, 20);
            this.rbGrade.Name = "rbGrade";
            this.rbGrade.Size = new System.Drawing.Size(94, 17);
            this.rbGrade.TabIndex = 2;
            this.rbGrade.TabStop = true;
            this.rbGrade.Text = "по 1-й оценке";
            this.rbGrade.UseVisualStyleBackColor = true;
            this.rbGrade.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // rbGroup
            // 
            this.rbGroup.AutoSize = true;
            this.rbGroup.Location = new System.Drawing.Point(85, 20);
            this.rbGroup.Name = "rbGroup";
            this.rbGroup.Size = new System.Drawing.Size(74, 17);
            this.rbGroup.TabIndex = 1;
            this.rbGroup.TabStop = true;
            this.rbGroup.Text = "по группе";
            this.rbGroup.UseVisualStyleBackColor = true;
            this.rbGroup.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // rbFullname
            // 
            this.rbFullname.AutoSize = true;
            this.rbFullname.Location = new System.Drawing.Point(7, 20);
            this.rbFullname.Name = "rbFullname";
            this.rbFullname.Size = new System.Drawing.Size(72, 17);
            this.rbFullname.TabIndex = 0;
            this.rbFullname.TabStop = true;
            this.rbFullname.Text = "по имени";
            this.rbFullname.UseVisualStyleBackColor = true;
            this.rbFullname.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(13, 69);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(162, 20);
            this.label1.TabIndex = 11;
            this.label1.Text = "Данные для поиска:";
            // 
            // tbFullname
            // 
            this.tbFullname.Location = new System.Drawing.Point(181, 71);
            this.tbFullname.Name = "tbFullname";
            this.tbFullname.Size = new System.Drawing.Size(100, 20);
            this.tbFullname.TabIndex = 12;
            this.tbFullname.TextChanged += new System.EventHandler(this.tbFullname_TextChanged);
            // 
            // tbGroup
            // 
            this.tbGroup.Location = new System.Drawing.Point(181, 71);
            this.tbGroup.Name = "tbGroup";
            this.tbGroup.Size = new System.Drawing.Size(100, 20);
            this.tbGroup.TabIndex = 13;
            this.tbGroup.TextChanged += new System.EventHandler(this.tbGroup_TextChanged);
            this.tbGroup.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tb_KeyPress);
            // 
            // tbGrade
            // 
            this.tbGrade.Location = new System.Drawing.Point(181, 71);
            this.tbGrade.Name = "tbGrade";
            this.tbGrade.Size = new System.Drawing.Size(100, 20);
            this.tbGrade.TabIndex = 14;
            this.tbGrade.TextChanged += new System.EventHandler(this.tbGrade_TextChanged);
            this.tbGrade.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tb_KeyPress);
            // 
            // btnClose
            // 
            this.btnClose.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnClose.Location = new System.Drawing.Point(76, 220);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(120, 40);
            this.btnClose.TabIndex = 15;
            this.btnClose.Text = "Закрыть";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // rtbCollection
            // 
            this.rtbCollection.Location = new System.Drawing.Point(12, 97);
            this.rtbCollection.Name = "rtbCollection";
            this.rtbCollection.Size = new System.Drawing.Size(269, 117);
            this.rtbCollection.TabIndex = 16;
            this.rtbCollection.Text = "";
            // 
            // FormSearch
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(293, 271);
            this.Controls.Add(this.rtbCollection);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.tbGrade);
            this.Controls.Add(this.tbGroup);
            this.Controls.Add(this.tbFullname);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.groupBox);
            this.Name = "FormSearch";
            this.Text = "FormSearch";
            this.groupBox.ResumeLayout(false);
            this.groupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox;
        private System.Windows.Forms.RadioButton rbGrade;
        private System.Windows.Forms.RadioButton rbGroup;
        private System.Windows.Forms.RadioButton rbFullname;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbFullname;
        private System.Windows.Forms.TextBox tbGroup;
        private System.Windows.Forms.TextBox tbGrade;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.RichTextBox rtbCollection;
    }
}
namespace LabApp
{
    partial class FormAddFromKeyboard
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
            this.btnAdd = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.lblFullname = new System.Windows.Forms.Label();
            this.lblGroup = new System.Windows.Forms.Label();
            this.lblGrade1 = new System.Windows.Forms.Label();
            this.lblGrade2 = new System.Windows.Forms.Label();
            this.lblGrade3 = new System.Windows.Forms.Label();
            this.lblGrade4 = new System.Windows.Forms.Label();
            this.lblGrade5 = new System.Windows.Forms.Label();
            this.tbGrade1 = new System.Windows.Forms.TextBox();
            this.tbGrade2 = new System.Windows.Forms.TextBox();
            this.tbGrade3 = new System.Windows.Forms.TextBox();
            this.tbGrade4 = new System.Windows.Forms.TextBox();
            this.tbGrade5 = new System.Windows.Forms.TextBox();
            this.tbFullname = new System.Windows.Forms.TextBox();
            this.tbGroup = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(189, 89);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(150, 50);
            this.btnAdd.TabIndex = 0;
            this.btnAdd.Text = "Добавить";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(17, 89);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(150, 50);
            this.btnCancel.TabIndex = 1;
            this.btnCancel.Text = "Отменить";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // lblFullname
            // 
            this.lblFullname.AutoSize = true;
            this.lblFullname.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblFullname.Location = new System.Drawing.Point(13, 13);
            this.lblFullname.Name = "lblFullname";
            this.lblFullname.Size = new System.Drawing.Size(160, 24);
            this.lblFullname.TabIndex = 2;
            this.lblFullname.Text = "Имя и инициалы:";
            // 
            // lblGroup
            // 
            this.lblGroup.AutoSize = true;
            this.lblGroup.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblGroup.Location = new System.Drawing.Point(13, 38);
            this.lblGroup.Name = "lblGroup";
            this.lblGroup.Size = new System.Drawing.Size(78, 24);
            this.lblGroup.TabIndex = 3;
            this.lblGroup.Text = "Группа:";
            // 
            // lblGrade1
            // 
            this.lblGrade1.AutoSize = true;
            this.lblGrade1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblGrade1.Location = new System.Drawing.Point(345, 11);
            this.lblGrade1.Name = "lblGrade1";
            this.lblGrade1.Size = new System.Drawing.Size(97, 24);
            this.lblGrade1.TabIndex = 4;
            this.lblGrade1.Text = "Оценка 1:";
            // 
            // lblGrade2
            // 
            this.lblGrade2.AutoSize = true;
            this.lblGrade2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblGrade2.Location = new System.Drawing.Point(345, 38);
            this.lblGrade2.Name = "lblGrade2";
            this.lblGrade2.Size = new System.Drawing.Size(97, 24);
            this.lblGrade2.TabIndex = 5;
            this.lblGrade2.Text = "Оценка 2:";
            // 
            // lblGrade3
            // 
            this.lblGrade3.AutoSize = true;
            this.lblGrade3.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblGrade3.Location = new System.Drawing.Point(345, 63);
            this.lblGrade3.Name = "lblGrade3";
            this.lblGrade3.Size = new System.Drawing.Size(97, 24);
            this.lblGrade3.TabIndex = 6;
            this.lblGrade3.Text = "Оценка 3:";
            // 
            // lblGrade4
            // 
            this.lblGrade4.AutoSize = true;
            this.lblGrade4.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblGrade4.Location = new System.Drawing.Point(345, 89);
            this.lblGrade4.Name = "lblGrade4";
            this.lblGrade4.Size = new System.Drawing.Size(97, 24);
            this.lblGrade4.TabIndex = 7;
            this.lblGrade4.Text = "Оценка 4:";
            // 
            // lblGrade5
            // 
            this.lblGrade5.AutoSize = true;
            this.lblGrade5.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblGrade5.Location = new System.Drawing.Point(345, 116);
            this.lblGrade5.Name = "lblGrade5";
            this.lblGrade5.Size = new System.Drawing.Size(97, 24);
            this.lblGrade5.TabIndex = 8;
            this.lblGrade5.Text = "Оценка 5:";
            // 
            // tbGrade1
            // 
            this.tbGrade1.Location = new System.Drawing.Point(448, 16);
            this.tbGrade1.Name = "tbGrade1";
            this.tbGrade1.Size = new System.Drawing.Size(100, 20);
            this.tbGrade1.TabIndex = 9;
            this.tbGrade1.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tb_KeyPress);
            // 
            // tbGrade2
            // 
            this.tbGrade2.Location = new System.Drawing.Point(448, 42);
            this.tbGrade2.Name = "tbGrade2";
            this.tbGrade2.Size = new System.Drawing.Size(100, 20);
            this.tbGrade2.TabIndex = 10;
            this.tbGrade2.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tb_KeyPress);
            // 
            // tbGrade3
            // 
            this.tbGrade3.Location = new System.Drawing.Point(448, 68);
            this.tbGrade3.Name = "tbGrade3";
            this.tbGrade3.Size = new System.Drawing.Size(100, 20);
            this.tbGrade3.TabIndex = 11;
            this.tbGrade3.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tb_KeyPress);
            // 
            // tbGrade4
            // 
            this.tbGrade4.Location = new System.Drawing.Point(448, 94);
            this.tbGrade4.Name = "tbGrade4";
            this.tbGrade4.Size = new System.Drawing.Size(100, 20);
            this.tbGrade4.TabIndex = 12;
            this.tbGrade4.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tb_KeyPress);
            // 
            // tbGrade5
            // 
            this.tbGrade5.Location = new System.Drawing.Point(448, 120);
            this.tbGrade5.Name = "tbGrade5";
            this.tbGrade5.Size = new System.Drawing.Size(100, 20);
            this.tbGrade5.TabIndex = 13;
            this.tbGrade5.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tb_KeyPress);
            // 
            // tbFullname
            // 
            this.tbFullname.Location = new System.Drawing.Point(180, 17);
            this.tbFullname.Name = "tbFullname";
            this.tbFullname.Size = new System.Drawing.Size(159, 20);
            this.tbFullname.TabIndex = 14;
            // 
            // tbGroup
            // 
            this.tbGroup.Location = new System.Drawing.Point(180, 43);
            this.tbGroup.Name = "tbGroup";
            this.tbGroup.Size = new System.Drawing.Size(159, 20);
            this.tbGroup.TabIndex = 15;
            this.tbGroup.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tb_KeyPress);
            // 
            // FormAddFromKeyboard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(572, 165);
            this.Controls.Add(this.tbGroup);
            this.Controls.Add(this.tbFullname);
            this.Controls.Add(this.tbGrade5);
            this.Controls.Add(this.tbGrade4);
            this.Controls.Add(this.tbGrade3);
            this.Controls.Add(this.tbGrade2);
            this.Controls.Add(this.tbGrade1);
            this.Controls.Add(this.lblGrade5);
            this.Controls.Add(this.lblGrade4);
            this.Controls.Add(this.lblGrade3);
            this.Controls.Add(this.lblGrade2);
            this.Controls.Add(this.lblGrade1);
            this.Controls.Add(this.lblGroup);
            this.Controls.Add(this.lblFullname);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnAdd);
            this.Name = "FormAddFromKeyboard";
            this.Text = "FormAddFromKeyboard";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Label lblFullname;
        private System.Windows.Forms.Label lblGroup;
        private System.Windows.Forms.Label lblGrade1;
        private System.Windows.Forms.Label lblGrade2;
        private System.Windows.Forms.Label lblGrade3;
        private System.Windows.Forms.Label lblGrade4;
        private System.Windows.Forms.Label lblGrade5;
        private System.Windows.Forms.TextBox tbGrade1;
        private System.Windows.Forms.TextBox tbGrade2;
        private System.Windows.Forms.TextBox tbGrade3;
        private System.Windows.Forms.TextBox tbGrade4;
        private System.Windows.Forms.TextBox tbGrade5;
        private System.Windows.Forms.TextBox tbFullname;
        private System.Windows.Forms.TextBox tbGroup;
    }
}
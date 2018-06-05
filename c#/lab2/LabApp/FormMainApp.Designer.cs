namespace LabApp
{
    partial class FormMainApp
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnAddFromKeyboard = new System.Windows.Forms.Button();
            this.btnAddFromFile = new System.Windows.Forms.Button();
            this.btnSaveToFile = new System.Windows.Forms.Button();
            this.btnSearchBy = new System.Windows.Forms.Button();
            this.btnShowAllByCondition = new System.Windows.Forms.Button();
            this.btnDelete = new System.Windows.Forms.Button();
            this.rtbCollection = new System.Windows.Forms.RichTextBox();
            this.lblStatus = new System.Windows.Forms.Label();
            this.groupBox = new System.Windows.Forms.GroupBox();
            this.rbGrade = new System.Windows.Forms.RadioButton();
            this.rbGroup = new System.Windows.Forms.RadioButton();
            this.rbFullname = new System.Windows.Forms.RadioButton();
            this.groupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnAddFromKeyboard
            // 
            this.btnAddFromKeyboard.Location = new System.Drawing.Point(16, 15);
            this.btnAddFromKeyboard.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnAddFromKeyboard.Name = "btnAddFromKeyboard";
            this.btnAddFromKeyboard.Size = new System.Drawing.Size(200, 62);
            this.btnAddFromKeyboard.TabIndex = 0;
            this.btnAddFromKeyboard.Text = "Добавить новый елемент с клавиатуры";
            this.btnAddFromKeyboard.UseVisualStyleBackColor = true;
            this.btnAddFromKeyboard.Click += new System.EventHandler(this.btnAddFromKeyboard_Click);
            // 
            // btnAddFromFile
            // 
            this.btnAddFromFile.Location = new System.Drawing.Point(16, 84);
            this.btnAddFromFile.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnAddFromFile.Name = "btnAddFromFile";
            this.btnAddFromFile.Size = new System.Drawing.Size(200, 62);
            this.btnAddFromFile.TabIndex = 1;
            this.btnAddFromFile.Text = "Добавить новые элементы из файла";
            this.btnAddFromFile.UseVisualStyleBackColor = true;
            this.btnAddFromFile.Click += new System.EventHandler(this.btnAddFromFile_Click);
            // 
            // btnSaveToFile
            // 
            this.btnSaveToFile.Location = new System.Drawing.Point(16, 153);
            this.btnSaveToFile.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnSaveToFile.Name = "btnSaveToFile";
            this.btnSaveToFile.Size = new System.Drawing.Size(200, 62);
            this.btnSaveToFile.TabIndex = 2;
            this.btnSaveToFile.Text = "Сохранить коллекцию в файл";
            this.btnSaveToFile.UseVisualStyleBackColor = true;
            this.btnSaveToFile.Click += new System.EventHandler(this.btnSaveToFile_Click);
            // 
            // btnSearchBy
            // 
            this.btnSearchBy.Location = new System.Drawing.Point(17, 222);
            this.btnSearchBy.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnSearchBy.Name = "btnSearchBy";
            this.btnSearchBy.Size = new System.Drawing.Size(200, 62);
            this.btnSearchBy.TabIndex = 4;
            this.btnSearchBy.Text = "Поиск элемента по заданному полю";
            this.btnSearchBy.UseVisualStyleBackColor = true;
            this.btnSearchBy.Click += new System.EventHandler(this.btnSearchBy_Click);
            // 
            // btnShowAllByCondition
            // 
            this.btnShowAllByCondition.Location = new System.Drawing.Point(17, 290);
            this.btnShowAllByCondition.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnShowAllByCondition.Name = "btnShowAllByCondition";
            this.btnShowAllByCondition.Size = new System.Drawing.Size(200, 62);
            this.btnShowAllByCondition.TabIndex = 5;
            this.btnShowAllByCondition.Text = "Показать все элементы, удовлетворяющие условию";
            this.btnShowAllByCondition.UseVisualStyleBackColor = true;
            this.btnShowAllByCondition.Click += new System.EventHandler(this.btnShowAllByCondition_Click);
            // 
            // btnDelete
            // 
            this.btnDelete.Location = new System.Drawing.Point(17, 359);
            this.btnDelete.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(200, 62);
            this.btnDelete.TabIndex = 6;
            this.btnDelete.Text = "Удалить элемент из коллекции";
            this.btnDelete.UseVisualStyleBackColor = true;
            this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
            // 
            // rtbCollection
            // 
            this.rtbCollection.Location = new System.Drawing.Point(225, 39);
            this.rtbCollection.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rtbCollection.Name = "rtbCollection";
            this.rtbCollection.Size = new System.Drawing.Size(351, 312);
            this.rtbCollection.TabIndex = 7;
            this.rtbCollection.Text = "";
            this.rtbCollection.TextChanged += new System.EventHandler(this.rtbCollection_TextChanged);
            // 
            // lblStatus
            // 
            this.lblStatus.AutoSize = true;
            this.lblStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblStatus.Location = new System.Drawing.Point(221, 15);
            this.lblStatus.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(271, 20);
            this.lblStatus.TabIndex = 8;
            this.lblStatus.Text = "Текущее состояние коллекции:";
            // 
            // groupBox
            // 
            this.groupBox.Controls.Add(this.rbGrade);
            this.groupBox.Controls.Add(this.rbGroup);
            this.groupBox.Controls.Add(this.rbFullname);
            this.groupBox.Location = new System.Drawing.Point(225, 359);
            this.groupBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox.Name = "groupBox";
            this.groupBox.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox.Size = new System.Drawing.Size(352, 62);
            this.groupBox.TabIndex = 9;
            this.groupBox.TabStop = false;
            this.groupBox.Text = "Сортировать";
            // 
            // rbGrade
            // 
            this.rbGrade.AutoSize = true;
            this.rbGrade.Location = new System.Drawing.Point(221, 25);
            this.rbGrade.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbGrade.Name = "rbGrade";
            this.rbGrade.Size = new System.Drawing.Size(88, 21);
            this.rbGrade.TabIndex = 2;
            this.rbGrade.TabStop = true;
            this.rbGrade.Text = "по баллу";
            this.rbGrade.UseVisualStyleBackColor = true;
            this.rbGrade.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // rbGroup
            // 
            this.rbGroup.AutoSize = true;
            this.rbGroup.Location = new System.Drawing.Point(113, 25);
            this.rbGroup.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbGroup.Name = "rbGroup";
            this.rbGroup.Size = new System.Drawing.Size(93, 21);
            this.rbGroup.TabIndex = 1;
            this.rbGroup.TabStop = true;
            this.rbGroup.Text = "по группе";
            this.rbGroup.UseVisualStyleBackColor = true;
            this.rbGroup.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // rbFullname
            // 
            this.rbFullname.AutoSize = true;
            this.rbFullname.Location = new System.Drawing.Point(9, 25);
            this.rbFullname.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbFullname.Name = "rbFullname";
            this.rbFullname.Size = new System.Drawing.Size(90, 21);
            this.rbFullname.TabIndex = 0;
            this.rbFullname.TabStop = true;
            this.rbFullname.Text = "по имени";
            this.rbFullname.UseVisualStyleBackColor = true;
            this.rbFullname.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // FormMainApp
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(593, 432);
            this.Controls.Add(this.groupBox);
            this.Controls.Add(this.lblStatus);
            this.Controls.Add(this.rtbCollection);
            this.Controls.Add(this.btnDelete);
            this.Controls.Add(this.btnShowAllByCondition);
            this.Controls.Add(this.btnSearchBy);
            this.Controls.Add(this.btnSaveToFile);
            this.Controls.Add(this.btnAddFromFile);
            this.Controls.Add(this.btnAddFromKeyboard);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "FormMainApp";
            this.Text = "LabApp";
            this.groupBox.ResumeLayout(false);
            this.groupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnAddFromKeyboard;
        private System.Windows.Forms.Button btnAddFromFile;
        private System.Windows.Forms.Button btnSaveToFile;
        private System.Windows.Forms.Button btnSearchBy;
        private System.Windows.Forms.Button btnShowAllByCondition;
        private System.Windows.Forms.Button btnDelete;
        private System.Windows.Forms.RichTextBox rtbCollection;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.GroupBox groupBox;
        private System.Windows.Forms.RadioButton rbGrade;
        private System.Windows.Forms.RadioButton rbGroup;
        private System.Windows.Forms.RadioButton rbFullname;
    }
}


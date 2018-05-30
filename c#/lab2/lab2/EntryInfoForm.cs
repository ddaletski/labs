using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace lab2
{
    public partial class EntryInfoForm : Form
    {
        public Student currentStudent;

        public EntryInfoForm()
        {
            InitializeComponent();
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            Visible = false;
        }


        private void textBoxName_TextChanged(object sender, EventArgs e)
        {
            currentStudent.Name = textBoxName.Text;
        }

        private void textBoxGroup_TextChanged(object sender, EventArgs e)
        {
            currentStudent.Group = Convert.ToUInt16(textBoxGroup.Text);
        }

        private void EntryInfoForm_VisibleChanged(object sender, EventArgs e)
        {
        }
    }
}

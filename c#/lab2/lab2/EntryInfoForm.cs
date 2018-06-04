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
        private List<ushort> marksList;


        public EntryInfoForm()
        {
            InitializeComponent();
            marksList = new List<ushort>();
            marksList.Add(1);
            marksList.Add(2);
            marksList.Add(3);
            marksList.Add(4);
            marksList.Add(5);
            dataGridViewRating.DataSource = marksList;
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            Visible = false;
        }


        private void textBoxName_TextChanged(object sender, EventArgs e)
        {
        }

        private void textBoxGroup_TextChanged(object sender, EventArgs e)
        {
        }

        private void EntryInfoForm_VisibleChanged(object sender, EventArgs e)
        {
        }

        private void dataGridViewRating_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            currentStudent.Name = textBoxName.Text;
            currentStudent.Group = Convert.ToUInt16(textBoxGroup.Text);
            for(int i = 0; i < 5; ++i)
            {
                currentStudent.Rating[i] = Convert.ToUInt16(marksList[i]);
                Console.WriteLine("mark: {0} = {1}", i, marksList[i]);
            }
        }
    }
}

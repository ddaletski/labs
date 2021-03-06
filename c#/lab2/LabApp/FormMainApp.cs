﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LabApp
{
    public partial class FormMainApp : Form
    {
        List<Student> collection = new List<Student>();

        public FormMainApp()
        {
            InitializeComponent();
        }

        private void btnAddFromKeyboard_Click(object sender, EventArgs e)
        {
            FormAddFromKeyboard form = new FormAddFromKeyboard();
            form.ShowDialog();
            if (form.isNew)
                collection.Add(form.GetStudent());
            Print();
        }

        private void btnAddFromFile_Click(object sender, EventArgs e)
        {
            Stream myStream = null;
            OpenFileDialog openFileDialog = new OpenFileDialog();

            openFileDialog.InitialDirectory = "c:\\";
            openFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    if ((myStream = openFileDialog.OpenFile()) != null)
                    {
                        using (myStream)
                        {
                            byte[] array = new byte[myStream.Length];
                            myStream.Read(array, 0, array.Length);
                            string textFromFile = Encoding.UTF8.GetString(array);
                            string[] lines = textFromFile.Split(new string[] { "\r\n" }, StringSplitOptions.RemoveEmptyEntries);
                            for (int i = 0; i < lines.Length; i+=3)
                            {
                                Student st = new Student();
                                st.fullName = lines[i];
                                st.group = Convert.ToUInt16(lines[i + 1]);
                                string[] grades = lines[i + 2].Split(',');
                                st.rating = new ushort[5];
                                for (int j = 0; j < grades.Length; j++)
                                {
                                    st.rating[j] = Convert.ToUInt16(grades[j]);
                                }
                                collection.Add(st);
                            }
                            Print();
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }
        }

        private void btnSaveToFile_Click(object sender, EventArgs e)
        {
            Stream myStream = null;
            SaveFileDialog saveFileDialog = new SaveFileDialog();

            saveFileDialog.InitialDirectory = "c:\\";
            saveFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            saveFileDialog.FilterIndex = 1;
            saveFileDialog.RestoreDirectory = true;

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    if ((myStream = saveFileDialog.OpenFile()) != null)
                    {
                        using (myStream)
                        {
                            byte[] input = { };
                            foreach (var item in collection)
                            {
                                string grades = "";
                                for (int i = 0; i < item.rating.Length; i++)
                                {
                                    grades += item.rating[i].ToString();
                                    if (i < item.rating.Length - 1) grades += ",";
                                }
                                input = Encoding.UTF8.GetBytes(item.fullName + Environment.NewLine 
                                    + item.group + Environment.NewLine 
                                    + grades + Environment.NewLine);
                                myStream.Write(input, 0, input.Length);
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }
        }

        private void Print()
        {
            rtbCollection.Clear();
            if (collection.Count > 0)
                foreach (var item in collection)
                {
                    rtbCollection.Text += "Fullname: " + item.fullName + "\n";
                    rtbCollection.Text += "Group: " + item.group + "\n";
                    rtbCollection.Text += "Rating:";
                    for (int i = 0; i < item.rating.Length; i++)
                    {
                        rtbCollection.Text += " " + item.rating[i];
                    }
                    rtbCollection.Text += "\n\n";
                }
        }

        private void btnSearchBy_Click(object sender, EventArgs e)
        {
            FormSearch form = new FormSearch(collection);
            form.ShowDialog();
        }

        private void btnShowAllByCondition_Click(object sender, EventArgs e)
        {
            FormCondition form = new FormCondition(collection);
            form.ShowDialog();
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            FormDeleteElement form = new FormDeleteElement();
            form.ShowDialog();
            if (form.isDelete)
            {
                if (collection.Count > form.index)
                {
                    collection.RemoveAt(form.index);
                    Print();
                }
            }
        }

        private void rb_CheckedChanged(object sender, EventArgs e)
        {
            if (rbFullname.Checked)
                collection.Sort((x, y) => x.fullName.CompareTo(y.fullName));
            else if (rbGrade.Checked)
                collection.Sort((x, y) => x.meanRating().CompareTo(y.meanRating()));
            else
                collection.Sort((x, y) => x.group.CompareTo(y.group));
            Print();
        }

        private void rtbCollection_TextChanged(object sender, EventArgs e)
        {

        }
    }
}

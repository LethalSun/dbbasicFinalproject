using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace dbProject
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void addVideoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 addVideo = new Form2();
            addVideo.Owner = this;
            addVideo.Show();
        }

        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex >= 0)
            {
                this.selectedIndex = comboBox1.SelectedIndex;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string searchString = textBox1.Text;
            if (selectedIndex == 0)
            {
                label1.Text = searchString;
            }
            else if (selectedIndex == 1)
            {
                label2.Text = searchString;
            }
            else
            {
                label3.Text = searchString;
            }
        }
    }
}
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LW5_PS1
{
    public partial class ImageForm : Form
    {
        public ImageForm(int width, int height)
        {
            InitializeComponent();

            // Задаем высоту, ширину окна
            this.Width = width + 45;
            this.Height = height + 70;

            // Задаем высоту ширину pictureBox
            pictureBoxImage.Width = width;
            pictureBoxImage.Height = height;

            this.Show();
        }

        public void DrawImage(Bitmap image)
        {
            pictureBoxImage.Image = image;
        }
    }
}

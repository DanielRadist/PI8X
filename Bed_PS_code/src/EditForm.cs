using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace LW5_PS1
{
    public partial class EditForm : Form
    {
        private ImageColorEditor _ColorEditor;  // Объект изменения картинки (внут. картинка)
        private ImageForm _ImageForm;           // Окно куда выводиться картинка


        //формат загружаемого файла
        private const string _filterFileDialog = "Image Files(*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG|All files (*.*)|*.*";

        public EditForm()
        {
            InitializeComponent();
            chartBright.Series[0].IsVisibleInLegend = false;
            chartBright.Titles.Add("Brightness");

            buttonLoad.Enabled = true;
            buttonSave.Enabled = false;
            buttonClose.Enabled = false;
        }

        private void ResetForm()
        {
            buttonLoad.Enabled = false;
            buttonSave.Enabled = true;
            buttonClose.Enabled = true;
            trackBarBrightness.Value = 0;
            labelBrightness.Text = String.Format("{0}", trackBarBrightness.Value);
            trackBarContrast.Value = 0;
            labelContrast.Text = String.Format("{0}", trackBarContrast.Value);
            trackBarRed.Value = 0;
            labelRed.Text = String.Format("{0}", trackBarRed.Value);
            trackBarGreen.Value = 0;
            labelGreen.Text = String.Format("{0}", trackBarGreen.Value);
            trackBarBlue.Value = 0;
            labelBlue.Text = String.Format("{0}", trackBarBlue.Value);
        }

        // Загрузить изображение
        private void buttonLoad_Click(object sender, EventArgs e)
        {
            openFileDialogLoad.Filter = _filterFileDialog;
            if (openFileDialogLoad.ShowDialog() == DialogResult.Cancel)
                return;

            if (_ImageForm != null)
                _ImageForm.Close();

            ResetForm();


            // содаем редактор
            _ColorEditor = new ImageColorEditor(new Bitmap(openFileDialogLoad.FileName));

            // создаем окно под вывод изображения
            _ImageForm = new ImageForm(_ColorEditor.currImageBmp.Width, _ColorEditor.currImageBmp.Height);

            // рисуем в окне ихображение
            _ImageForm.DrawImage(_ColorEditor.currImageBmp);
            crateChart(_ColorEditor.currImageBmp);
        }

        // Закрыть изображение
        private void buttonClose_Click(object sender, EventArgs e)
        {
            _ImageForm.Close();
            _ColorEditor = null;

            buttonLoad.Enabled = true;
            buttonSave.Enabled = false;
            buttonClose.Enabled = false;
        }

        // Сохранить изображение
        private void buttonSave_Click(object sender, EventArgs e)
        {
            saveFileDialog.Filter = _filterFileDialog;
            if (saveFileDialog.ShowDialog() == DialogResult.Cancel)
                return;

            _ColorEditor.ImageBmp.Save(saveFileDialog.FileName);
        }

        private void crateChart(Bitmap Image)
        {
            chartBright.Series.Clear();
            chartBright.Series.Add("Bright");
            chartBright.Series[0].IsVisibleInLegend = false;

            int[] valuesBright = new int[_ColorEditor.sizeColor];

            for (int i = 0; i < _ColorEditor.sizeColor; i++)
                valuesBright[i] = 0;

            for (int i = 0; i < Image.Width; i++)
                for (int j = 0; j < Image.Height; j++)
                {
                    valuesBright[_ColorEditor.GetBrightnessPixel(i, j, Image)]++;
                }

            for (int i = 0; i < _ColorEditor.sizeColor; i++)
                chartBright.Series[0].Points.Add(valuesBright[i]);
        }

        // Применение изменений
        private void ApplyChangeImage()
        {
            int brightRed = trackBarRed.Value;
            int brightGreen = trackBarGreen.Value;
            int brightBlue = trackBarBlue.Value;

            _ColorEditor.ChangeContrast(trackBarContrast.Value, _ColorEditor.ImageBmp);
            _ColorEditor.ChangeBright(
                trackBarBrightness.Value + brightRed,
                trackBarBrightness.Value + brightGreen,
                trackBarBrightness.Value + brightBlue,
                _ColorEditor.currImageBmp
                );
            _ImageForm.DrawImage(_ColorEditor.currImageBmp);
            crateChart(_ColorEditor.currImageBmp);
        }

        // Изменение яркости

        private void trackBarBrightness_Scroll(object sender, EventArgs e)
        {
            labelBrightness.Text = String.Format("{0}", trackBarBrightness.Value);
            ApplyChangeImage();
        }

        // Изменение контрастности

        private void trackBarContrast_Scroll(object sender, EventArgs e)
        {
            labelContrast.Text = String.Format("{0}", trackBarContrast.Value);
            ApplyChangeImage();
        }

        // бинаризация

        private void trackBarToBlackWhite_Scroll(object sender, EventArgs e)
        {
            labelToBlackWhite.Text = String.Format("{0}", trackBarToBlackWhite.Value);
            _ColorEditor.ChangeToBlackWhite(trackBarToBlackWhite.Value, _ColorEditor.ImageBmp);
            _ImageForm.DrawImage(_ColorEditor.currImageBmp);
        }

        // регулирование яркости каналов

        private void trackBarRed_Scroll(object sender, EventArgs e)
        {
            labelRed.Text = String.Format("{0}", trackBarRed.Value);
            trackBarBrightness_Scroll(sender, e);
        }

        private void trackBarGreen_Scroll(object sender, EventArgs e)
        {
            labelGreen.Text = String.Format("{0}", trackBarGreen.Value);
            trackBarBrightness_Scroll(sender, e);
        }

        private void trackBarBlue_Scroll(object sender, EventArgs e)
        {
            labelBlue.Text = String.Format("{0}", trackBarBlue.Value);
            trackBarBrightness_Scroll(sender, e);
        }

        private void buttonApply_Click(object sender, EventArgs e)
        {
            _ColorEditor.Apply();
            ResetForm();
        }

        private void buttonGray_Click(object sender, EventArgs e)
        {
            _ColorEditor.SetCurrImage(_ColorEditor.GrayScale(_ColorEditor.currImageBmp));
            _ImageForm.DrawImage(_ColorEditor.currImageBmp);
        }

        private void buttonNegative_Click(object sender, EventArgs e)
        {
            _ColorEditor.SetCurrImage(_ColorEditor.Negative(_ColorEditor.currImageBmp));
            _ImageForm.DrawImage(_ColorEditor.currImageBmp);
        }
    }
}

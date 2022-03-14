using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace LW5_PS1
{
    public class ImageColorEditor
    {
        public readonly int sizeColor = 256;       // кол-во вариантов яроксти цвета в пикселе
        public readonly int maxColor = 255;        // максимальная яркость одного цвета в пикселе
        public readonly int minColor = 0;          // минимальная ярокость одного цвета в пискеле
        public readonly int countColor = 3;        // кол-во основных цветов в пикселе


        // исходное изображение
        public Bitmap ImageBmp { get; private set; }

        // текущее изображение
        public Bitmap currImageBmp { get; private set; }

        public ImageColorEditor(Bitmap image)
        {
            ImageBmp = image;
            currImageBmp = new Bitmap(image);
        }

        public void Apply()
        {
            ImageBmp = new Bitmap(currImageBmp);
        }

        public void SetCurrImage(Bitmap image)
        {
            currImageBmp = image;
        }

        public static int ToByte(int Val) 
        {
            if (Val > 255)
                return 255;
            else if (Val < 0)
                return 0;
            return Val;
        }


        // Изменение яркости изображения [-255 ; 255]
        public Bitmap ChangeBright(int brightR, int brightG, int brightB, Bitmap Image)
        {
            for (int i = 0; i < Image.Width; i++)
                for (int j = 0; j < Image.Height; j++)
                {
                    Color src = Image.GetPixel(i, j);
                    currImageBmp.SetPixel(i, j, Color.FromArgb(
                        ToByte(src.R + brightR),
                        ToByte(src.G + brightG),
                        ToByte(src.B + brightB)
                        ));
                }

            return currImageBmp;
        }
        // Изменение контрастности изображения [-100 ; 100]
        public Bitmap ChangeContrast(int value, Bitmap Image)
        {
            double contrast = (100.0 + value) / 100.0; //Вычисляем общее значение контраста
            contrast *= contrast;

            for (int i = 0; i < Image.Width; i++)
                for (int j = 0; j < Image.Height; j++)
                {
                    Color src = Image.GetPixel(i, j);

                    double pixelR = (src.R) / 255.0;
                    pixelR -= 0.5;
                    pixelR *= contrast;
                    pixelR += 0.5;
                    pixelR *= 255;

                    double pixelG = (src.G) / 255.0;
                    pixelG -= 0.5;
                    pixelG *= contrast;
                    pixelG += 0.5;
                    pixelG *= 255;

                    double pixelB = (src.B) / 255.0;
                    pixelB -= 0.5;
                    pixelB *= contrast;
                    pixelB += 0.5;
                    pixelB *= 255;

                    currImageBmp.SetPixel(i, j, Color.FromArgb(
                        ToByte(Convert.ToInt32(pixelR)),
                        ToByte(Convert.ToInt32(pixelG)),
                        ToByte(Convert.ToInt32(pixelB))
                        ));
                }
            return currImageBmp;
        }

        // Бинаризация изображения [0; 255]
        public Bitmap ChangeToBlackWhite(int treshold, Bitmap Image)
        {
            for (int i = 0; i < Image.Width; i++)
                for (int j = 0; j < Image.Height; j++)
                {
                    Color src = Image.GetPixel(i, j);
                    currImageBmp.SetPixel(i, j, (GetBrightnessPixel(i, j, Image) < treshold ? Color.Black : Color.White));
                }
            return currImageBmp;
        }


        public int GetBrightnessPixel(int width, int height, Bitmap Image)
        {
            Color color = Image.GetPixel(width, height);
            return (int)(0.299 * color.R + 0.5876 * color.G + 0.114 * color.B);
        }

        public Bitmap GrayScale(Bitmap Image)
        {
            for (int i = 0; i < Image.Width; i++)
                for (int j = 0; j < Image.Height; j++)
                {
                    int brightness = GetBrightnessPixel(i, j, Image);
                    currImageBmp.SetPixel(i, j, Color.FromArgb(brightness, brightness, brightness));
                }
            return currImageBmp;
        }

        public Bitmap Negative(Bitmap Image)
        {
            for (int i = 0; i < Image.Width; i++)
                for (int j = 0; j < Image.Height; j++)
                {
                    Color SrcColor = Image.GetPixel(i, j);
                    int brightness = GetBrightnessPixel(i, j, Image);
                    currImageBmp.SetPixel(i, j, Color.FromArgb(maxColor - SrcColor.R, maxColor - SrcColor.G, maxColor - SrcColor.B));
                }
            return currImageBmp;
        }
    }
}

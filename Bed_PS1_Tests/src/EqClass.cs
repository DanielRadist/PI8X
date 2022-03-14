using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bed_PS1_Tests.src
{
    public static class EqClass
    {
        public static bool EqImages(Bitmap img1, Bitmap img2)
        {
            if (img1.Size == img2.Size)
            {
                for (int i = 0; i < img1.Width; i++)
                    for (int j = 0; j < img1.Height; j++)
                        if (img1.GetPixel(i, j) != img2.GetPixel(i, j))
                            return false;
                return true;
            }
            else
                return false;
        }

        /// <summary>
        /// Сравнение средней ярокости картинок
        /// </summary>
        /// <returns>1 - img1 ярче, 0 - одинаковы, -1 - img2 ярче</returns>
        public static int EqBrightImages (Bitmap img1, Bitmap img2)
        {
            float brightImg1 = 0;
            int countImg1 = 0;
            float brightImg2 = 0;
            int countImg2 = 0;

            for (int i = 0; i < img1.Width; i++)
                for (int j = 0; j < img1.Height; j++)
                {
                    brightImg1 += img1.GetPixel(i, j).GetBrightness();
                    countImg1++;
                }

            for (int i = 0; i < img2.Width; i++)
                for (int j = 0; j < img2.Height; j++)
                {
                    brightImg2 += img2.GetPixel(i, j).GetBrightness();
                    countImg2++;
                }

            if ((brightImg1 / countImg1) > (brightImg2 / countImg2))
                return 1;
            else if ((brightImg1 / countImg1) < (brightImg2 / countImg2))
                return -1;
            else
                return 0;
        }

        /// <summary>
        /// Сравнение средней контрастности картинок
        /// </summary>
        /// <returns>1 - img1 ярче, 0 - одинаковы, -1 - img2 ярче</returns>
        public static int EqContrastImages(Bitmap img1, Bitmap img2)
        {
            float brightImg1 = 0;
            int countImg1 = 0;
            float brightImg2 = 0;
            int countImg2 = 0;

            for (int i = 0; i < img1.Width; i++)
                for (int j = 0; j < img1.Height; j++)
                {
                    brightImg1 += img1.GetPixel(i, j).GetSaturation();
                    countImg1++;
                }

            for (int i = 0; i < img2.Width; i++)
                for (int j = 0; j < img2.Height; j++)
                {
                    brightImg2 += img2.GetPixel(i, j).GetSaturation();
                    countImg2++;
                }

            if ((brightImg1 / countImg1) > (brightImg2 / countImg2))
                return 1;
            else if ((brightImg1 / countImg1) < (brightImg2 / countImg2))
                return -1;
            else
                return 0;
        }
    }
}

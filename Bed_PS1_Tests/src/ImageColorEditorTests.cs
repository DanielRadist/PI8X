using Microsoft.VisualStudio.TestTools.UnitTesting;
using LW5_PS1;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using Bed_PS1_Tests.src;
using System.IO;

namespace LW5_PS1.Tests
{
    [TestClass()]
    public class ImageColorEditorTests
    {
        
        [TestMethod()]
        [DataRow(@"..\..\img\test_img.jpg")]
        public void ImageColorEditorTest(string fileName)
        {
            // arrane
            Bitmap srcImg = new Bitmap(fileName);

            // act Проверка правильности создания копии исхоного изображения
            var imgEdit = new ImageColorEditor(srcImg);
            Bitmap newImg = imgEdit.currImageBmp;

            // assert
            if (srcImg == null)
                Assert.Fail();
            Assert.IsTrue(EqClass.EqImages(srcImg, newImg));
        }

        [TestMethod()]
        [DataRow(@"..\..\img\test_img.jpg")]
        public void ApplyTest(string fileName)
        {
            // arrane
            Bitmap srcImg = new Bitmap(fileName);

            // act Проверка логики кнопки "Применить" после изменения изображения
            var imgEdit = new ImageColorEditor(srcImg);
            imgEdit.ChangeContrast(100, imgEdit.currImageBmp);
            imgEdit.Apply();

            // assert
            if (srcImg == null)
                Assert.Fail();
            Assert.IsTrue(EqClass.EqImages(imgEdit.currImageBmp, imgEdit.ImageBmp));
        }

        [TestMethod()]
        [DataRow(-1)]
        [DataRow(0)]
        [DataRow(180)]
        [DataRow(255)]
        [DataRow(256)]
        public void ToByteTest(int value)
        {
            // arrane
            int returnMin = 0;
            int returnMax = 255;

            // act
            var returnVal = ImageColorEditor.ToByte(value);

            // assert
            Assert.IsTrue(returnVal >= returnMin && returnVal <= returnMax);
        }

        [TestMethod()]
        [DataRow(1, 0, 0, @"..\..\img\test_img.jpg")]
        [DataRow(0, 1, 0, @"..\..\img\test_img.jpg")]
        [DataRow(0, 0, 1, @"..\..\img\test_img.jpg")]
        [DataRow(1000, 0, 0, @"..\..\img\test_img.jpg")]
        [DataRow(0, 1000, 0, @"..\..\img\test_img.jpg")]
        [DataRow(0, 0, 1000, @"..\..\img\test_img.jpg")]
        public void ChangeBrightUpTest(int upR, int upG, int upB, string fileName)
        {
            // arrane
            Bitmap img = new Bitmap(fileName);
            ImageColorEditor imgEdit = new ImageColorEditor(img);

            // act: Изменение яркости пискеля в большую сторону по цветам.
            Bitmap newImg = imgEdit.ChangeBright(upR, upG, upB, img);

            // asert
            Assert.IsTrue(EqClass.EqBrightImages(newImg, img) == 1);
        }

        [TestMethod()]
        [DataRow(-1, 0, 0, @"..\..\img\test_img.jpg")]
        [DataRow(0, -1, 0, @"..\..\img\test_img.jpg")]
        [DataRow(0, 0, -1, @"..\..\img\test_img.jpg")]
        [DataRow(-1000, 0, 0, @"..\..\img\test_img.jpg")]
        [DataRow(0, -1000, 0, @"..\..\img\test_img.jpg")]
        [DataRow(0, 0, -1000, @"..\..\img\test_img.jpg")]
        public void ChangeBrightDownTest(int upR, int upG, int upB, string fileName)
        {
            // arrane
            Bitmap img = new Bitmap(fileName);
            ImageColorEditor imgEdit = new ImageColorEditor(img);

            // act: Изменение яркости пискеля в меньшую сторону по цветам.
            Bitmap newImg = imgEdit.ChangeBright(upR, upG, upB, img);

            // asert
            Assert.IsTrue(EqClass.EqBrightImages(newImg, img) == -1);
        }

        [TestMethod()]
        [DataRow(1, @"..\..\img\test_img.jpg")]
        [DataRow(2, @"..\..\img\test_img.jpg")]
        [DataRow(100, @"..\..\img\test_img.jpg")]
        public void ChangeContrastUpTest(int value, string fileName)
        {
            // arrane
            Bitmap img = new Bitmap(fileName);
            ImageColorEditor imgEdit = new ImageColorEditor(img);

            // act: Изменение контрастности пискеля в большую сторону
            Bitmap newImg = imgEdit.ChangeContrast(value, img);

            // asert
            Assert.IsTrue(EqClass.EqContrastImages(newImg, img) == 1);
        }

        [TestMethod()]
        [DataRow(-1, @"..\..\img\test_img.jpg")]
        [DataRow(-2, @"..\..\img\test_img.jpg")]
        [DataRow(-100, @"..\..\img\test_img.jpg")]
        public void ChangeContrastDownTest(int value, string fileName)
        {
            // arrane
            Bitmap img = new Bitmap(fileName);
            ImageColorEditor imgEdit = new ImageColorEditor(img);

            // act: Изменение контрастности пискеля в меньшую сторон
            Bitmap newImg = imgEdit.ChangeContrast(value, img);

            // asert
            Assert.IsTrue(EqClass.EqContrastImages(newImg, img) == -1);
        }

        [TestMethod()]
        [DataRow(0, @"..\..\img\test_img.jpg")]
        [DataRow(10, @"..\..\img\test_img.jpg")]
        [DataRow(30, @"..\..\img\test_img.jpg")]
        [DataRow(60, @"..\..\img\test_img.jpg")]
        [DataRow(120, @"..\..\img\test_img.jpg")]
        [DataRow(255, @"..\..\img\test_img.jpg")]
        public void ChangeToBlackWhiteTest(int value, string fileName)
        {
            Bitmap img = new Bitmap(fileName);

            ImageColorEditor imgEdior = new ImageColorEditor(img);
            Bitmap newImg = imgEdior.ChangeToBlackWhite(value, img);

            for (int i = 0; i < newImg.Width; i++)
                for (int j = 0; j < newImg.Height; j++)
                {
                    var pixel = newImg.GetPixel(i, j);

                    if (pixel.R == 255 && pixel.G == 255 && pixel.B == 255) //white
                        continue;
                    else if (pixel.R == 0 && pixel.G == 0 && pixel.B == 0)  //black
                        continue;
                    else
                        Assert.Fail();
                }
        }

        [TestMethod()]
        [DataRow(@"..\..\img\test_img.jpg")]
        public void GrayScaleTest(string fileName)
        {
            Bitmap img = new Bitmap(fileName);

            ImageColorEditor imgEdior = new ImageColorEditor(img);
            Bitmap newImg = imgEdior.GrayScale(img);

            for (int i = 0; i < newImg.Width; i++)
                for (int j = 0; j < newImg.Height; j++)
                {
                    var pixel = newImg.GetPixel(i, j);
                    if (!(pixel.R == pixel.G && pixel.R == pixel.B))
                    {
                        Assert.Fail();
                        return;
                    }
                }
        }

        [TestMethod()]
        [DataRow(@"..\..\img\test_img.jpg")]
        public void NegativeTest(string fileName)
        {
            Bitmap img = new Bitmap(fileName);

            ImageColorEditor imgEdior = new ImageColorEditor(img);
            Bitmap newImg = imgEdior.Negative(img);

            for (int i = 0; i < newImg.Width; i++)
                for (int j = 0; j < newImg.Height; j++)
                {
                    var pixNew = newImg.GetPixel(i, j);
                    var pixSrc = img.GetPixel(i, j);
                    if (!((255 - pixSrc.R == pixNew.R) && (255 - pixSrc.G == pixNew.G) && (255 - pixSrc.B == pixNew.B)))
                    {
                        Assert.Fail();
                        return;
                    }
                }
        }
    }
}
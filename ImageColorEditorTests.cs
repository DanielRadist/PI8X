using Microsoft.VisualStudio.TestTools.UnitTesting;
using LW5_PS1;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;

namespace LW5_PS1.Tests
{
    [TestClass()]
    public class ImageColorEditorTests
    {
        [TestMethod()]
        public void ToByte_Test(int value)
        {
            // arrane
            int returnMin = 0;
            int returnMax = 255;

            // act
            var retValue = ImageColorEditor.ToByte(value);

            // assert
            Assert.InRange(retValue, returnMin, returnMax);
        }

        [TestMethod()]
        public void ChangeBrightTest()
        {
            Bitmap img = new Bitmap(1, 1);
            Assert.Fail();
        }
    }
}
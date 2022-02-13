using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LW5_PS1
{
    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// framework 4.7.2
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new EditForm());
        }
    }
}

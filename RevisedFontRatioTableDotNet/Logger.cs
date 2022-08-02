using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace RevisedFontRatioTableDotNet
{
    public class Logger
    {
        private static Logger singleton;
        private readonly string logFilePath;
        private StreamWriter writer;

        public static void SetFilePath(string logFilePath)
        {
            if (singleton == null)
            {
                singleton = new Logger(logFilePath);
            }
        }

        public static Logger GetInstance()
        {
            if (singleton == null)
            {
                singleton = new Logger(Properties.Resources.LOG_FILENAME);
            }

            return singleton;
        }

        private Logger(string logFilePath)
        {
            this.logFilePath = logFilePath;

            // ログファイルを生成する
            CreateLogFile(new FileInfo(this.logFilePath));
        }

        public void Log(string msg)
        {
            Out(msg);
        }

        private void Out(string msg)
        {
            string fullMessage = string.Format(
                "[{0}] {1}",
                DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff"),
                msg
                );

            this.writer.WriteLine(fullMessage);
        }

        private void CreateLogFile(FileInfo logFile)
        {
            if (!Directory.Exists(logFile.DirectoryName))
            {
                Directory.CreateDirectory(logFile.DirectoryName);
            }

            this.writer = new StreamWriter(logFile.FullName, true, Encoding.UTF8)
            {
                AutoFlush = true
            };
        }
    }
}

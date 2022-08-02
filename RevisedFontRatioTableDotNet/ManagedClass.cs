using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Reflection;
using System.IO;
using System.Text;


namespace RevisedFontRatioTableDotNet
{
    public class ManagedClass
    {
        /// <summary>
        /// テキストキャスト名のリスト
        /// </summary>
        List<string> textCastNames;

        /// <summary>
        /// テキストキャスト名からキャスト番号を引く辞書
        /// </summary>
        Dictionary<string, UInt32> textNameToIndexDict;

        /// <summary>
        /// テキスト着せ替え用生成コード
        /// </summary>
        string outputTableCode;

        /// <summary>
        /// SDKプロジェクトファイルパス
        /// </summary>
        string projectFilePath;

        /// <summary>
        /// SDKプロジェクト名
        /// </summary>
        string projectName;

        /// <summary>
        /// 出力スクリプト名
        /// </summary>
        string outputScriptName;

        public ManagedClass()
        {
            string location = Assembly.GetExecutingAssembly().Location;
            location = Path.GetDirectoryName(location) + "\\" + Properties.Resources.WRAPPER_DLL_FILENAME;

            Assembly a = Assembly.LoadFrom(location);

            // 設定ファイルパスと配置フォルダ
            //this.localToolFolder = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData) + "\\" + Properties.Resources.TOOL_NAME;
            //this.settingFilePath = this.localToolFolder + "\\" + Properties.Resources.SETTING_FILE;
        }

        /// <summary>
        /// ツール処理開始
        /// </summary>
        /// <returns>true:処理完了、false:処理キャンセル</returns>
        public bool BeginProcess()
        {
            bool result = false;

            // 出力スクリプト名を指定
            this.outputScriptName = Properties.Resources.OUTPUT_SCRIPT_CAST_NAME;

            // text cast data processing before processing excel sheet
            this.textNameToIndexDict = new Dictionary<string, UInt32>();

            // create Dictionary, key: text cast name, value: text cast number
            for (int i = 0; i < this.textCastNames.Count; i++)
            {
                string textCastName = this.textCastNames[i];
                this.textNameToIndexDict[textCastName] = (UInt32)i;
            }

            var excelReader = new DataExcel.ExcelReader(this.textNameToIndexDict, this.textCastNames.Count);
            if (excelReader.OpenFontExcel())
            {
                this.outputTableCode = excelReader.OutputCode;
                result = true;
            }
            else
            {
                MessageBox.Show("Read Failed.");
            }

            return result;
        }

        /// <summary>
        /// プロジェクトファイルのファイルパス、名前を元に関係性ファイルの名前、パスをUIへ送る
        /// </summary>
        /// <param name="filepathObj">プロジェクトファイルパス</param>
        /// <param name="projectnameObj">プロジェクト名</param>
        public void UploadProjectInfo(object filepathObj, object projectnameObj)
        {
            this.projectFilePath = filepathObj as string;
            this.projectName = projectnameObj as string;
        }

        /// <summary>
        /// .NET側へのテキストキャスト名文字列転送処理
        /// </summary>
        /// <param name="names">テキストキャスト名配列</param>
        public void UploadTextCastNames(object[] names)
        {
            var query = names.Select(name => name as string);

            this.textCastNames = query.ToList();
        }

        /// <summary>
        /// dll側へ生成スクリプトキャスト名を転送
        /// </summary>
        /// <returns>スクリプト名</returns>
        public string DownloadTableScriptName()
        {
            return this.outputScriptName;
        }

        /// <summary>
        /// dll側へ生成コードを転送
        /// </summary>
        /// <returns>スクリプトキャストコード</returns>
        public string DownloadTableScriptCode()
        {
            return this.outputTableCode;
        }
    }
}

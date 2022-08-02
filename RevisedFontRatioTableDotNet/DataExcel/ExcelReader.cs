using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Excel = Microsoft.Office.Interop.Excel;
using System.Reflection;
using System.Runtime.InteropServices;

namespace RevisedFontRatioTableDotNet.DataExcel
{
    /// <summary>
    /// テキスト着せ替え用データ定義Excelファイル読み取りクラス
    /// </summary>
    public class ExcelReader
    {
        /// <summary>
        /// Multi Language Table Excelファイルパス
        /// </summary>
        public string FilePathMultiLang { get; private set; }

        /// <summary>
        /// Font Color定義書Excelファイルパス
        /// </summary>
        public string FilePathFontColor { get; private set; }

        /// <summary>
        /// 出力スクリプト文字列
        /// </summary>
        public string OutputCode { get; private set; }

        /// <summary>
        /// テキストキャスト名からキャスト番号を引く辞書
        /// </summary>
        private Dictionary<string, UInt32> nameToIndexDictionary;

        /// <summary>
        /// テキストキャスト名の数（リストの空白も含む）
        /// </summary>
        private int textCastCountWithEmpty;

        public ExcelReader(Dictionary<string, UInt32> textCastNameToIndexDict, int textCastCount)
        {
            this.nameToIndexDictionary = textCastNameToIndexDict;
            this.textCastCountWithEmpty = textCastCount;
        }



        /// <summary>
        /// テキスト着せ替え用データ定義Excelファイルの読み取りから長体率テーブルの生成まで
        /// </summary>
        /// <returns>処理成否</returns>
        public bool OpenFontExcel()
        {
            const int COL_CAST_NAME_MULTI = 5;     // Layer Name(cast name)列（E列:5）
            const int COL_FONT_SCALE_MULTI = 7;    // 長体率列（G列:7）
            const int COL_STRING_ID_MULTI = 9;     // String ID列（I列:9）
            const int COL_ORIGINAL_STRING_MULTI = 10; // Original String列（J列:10）
            const string USE_RANGE_MULTI = "A1:J"; // 対象range表記

            const int COL_CAST_NAME_SINGLE = 6;     // Layer Name(cast name)列（F列:6）
            const int COL_FONT_SCALE_SINGLE = 8;    // 長体率列（H列:8）
            const string USE_RANGE_SINGLE = "A1:H"; // 対象range表記

            const int COL_BASIS_CHECK_ROW_LENGTH_MULTI = 1; // 行数カウントのための基準列（A列:1）
            const int COL_BASIS_CHECK_ROW_LENGTH_SINGLE = 2; // 行数カウントのための基準列（B列:2）


            // Multi Lang Table Get Length 多言語対応シート名
            string MLTABLE_GET_LENGTH_SHEET_NAME_MULTI = Properties.Resources.MLTABLE_GET_LENGTH_SHEET_NAME_MULTI;
            // Multi Lang Table Get Length 単言語シート名
            string MLTABLE_GET_LENGTH_SHEET_NAME_SINGLE = Properties.Resources.MLTABLE_GET_LENGTH_SHEET_NAME_SINGLE;

            Logger logger = Logger.GetInstance();

            bool result = false;

            // Multi Language Table GetLength Excelファイルパス用のファイルダイアログ展開
            this.FilePathMultiLang = GetFileNameFromOpenFileDialog("Select Multi Language Table GetLength Excel file");
            if (string.IsNullOrWhiteSpace(this.FilePathMultiLang))
            {
                return result;
            }

            MLWord[] mlWordArray = new MLWord[textCastCountWithEmpty];
            int gCheckIndexRow;
            // 各finallyブロックで、アクセスしたExcel COMオブジェクトをReleaseする必要がある
            // （Release忘れでプロセスが残り、次のExcelファイル展開時に例外発生する）ので
            // 参照するオブジェクトを１段階ずつ変数に保持しておく
            try
            {
                // Excel Application block
                var excelApp = new Excel.Application();
                try
                {
                    // Workbooks block
                    Excel.Workbooks oWBs = excelApp.Workbooks;
                    try
                    {
                        // Workbook block (MultiLangTable GetLength)
                        // Multi Language Tableエクセルを展開する
                        Excel.Workbook oWorkbookMultiLang = oWBs.Open(this.FilePathMultiLang);
                        try
                        {
                            logger.Log($"Multi Lang Table Opend: {this.FilePathMultiLang}");

                            // Sheets block
                            Excel.Sheets worksheets = oWorkbookMultiLang.Sheets;
                            try
                            {
                                // Worksheet(MultiLang) block
                                var sheetML = worksheets[MLTABLE_GET_LENGTH_SHEET_NAME_MULTI];
                                try
                                {
                                    logger.Log("Multi Lang Sheet Opened.");

                                    // シートの行数を測る
                                    int rowCount;
                                    var columns = sheetML.Columns;
                                    var cols = columns[COL_BASIS_CHECK_ROW_LENGTH_MULTI];
                                    var colsFound = cols.Find("*", SearchOrder: Excel.XlSearchOrder.xlByRows, SearchDirection: Excel.XlSearchDirection.xlPrevious);
                                    rowCount = colsFound.Row;
                                    Marshal.ReleaseComObject(colsFound);
                                    Marshal.ReleaseComObject(cols);
                                    Marshal.ReleaseComObject(columns);


                                    // 使用範囲を一括で二次元配列にコピー
                                    // Cells[r,c]を使ってアクセスすると、参照速度が極端に遅くなるため
                                    // 一度、参照範囲のセル値をコピーしておく
                                    Object[,] rangeArray;
                                    Excel.Range usedRange = sheetML.Range[USE_RANGE_MULTI + rowCount.ToString()];

                                    try
                                    {
                                        // 参照範囲のセルデータを一括コピー
                                        rangeArray = usedRange.Value;
                                    }
                                    finally { Marshal.ReleaseComObject(usedRange); }

                                    // 二次元配列に対してループを回す
                                    int lastRow = rangeArray.GetLength(0);
                                    for (int indexRow = 2; indexRow <= lastRow; indexRow++)
                                    {
                                        gCheckIndexRow = indexRow;
                                        // キャスト名 (cast name)列
                                        string castName = (string)rangeArray[indexRow, COL_CAST_NAME_MULTI];
                                        // 長体率列
                                        double fontRate = CellObjReadToRate(rangeArray[indexRow, COL_FONT_SCALE_MULTI]);
                                        // 文字列ID (String ID)列
                                        string stringID = (string)rangeArray[indexRow, COL_STRING_ID_MULTI];
                                        // オリジナル文字列 (Original String)列
                                        string originalString = CellObjReadToString(rangeArray[indexRow, COL_ORIGINAL_STRING_MULTI]);

                                        // SDKのテキストキャストの中から探し出すキャスト名を合成(CastName + "_" + StringID)する
                                        // どちらかの名前がなければ（空白ならば）スキップ
                                        if (string.IsNullOrWhiteSpace(castName) || string.IsNullOrWhiteSpace(stringID))
                                        {
                                            continue;
                                        }

                                        // 前後の空白を除去
                                        castName = castName.Trim();
                                        stringID = stringID.Trim();

                                        // Cast Name単体とCastName + "_" + StringID複合のいずれの文字列も
                                        // テキストキャスト名リストでマッチングさせてキャスト番号を取得する
                                        // ================================================================
                                        string targetTextCastNameSingle = castName;
                                        string targetTextCastNameConnected = $"{castName}_{stringID}";

                                        // SDKのテキストキャストの辞書からキャスト番号を取得する。
                                        // キャスト名が見つかった場合のみ登録
                                        if (this.nameToIndexDictionary.ContainsKey(targetTextCastNameSingle))
                                        {
                                            // テキストキャスト番号
                                            uint number = this.nameToIndexDictionary[targetTextCastNameSingle];

                                            // 既にキャスト番号に対応した長体率が登録されているかどうかを確認して
                                            // 登録されていれば、上書き処理をログ処理する
                                            if (mlWordArray[(int)number] != null)
                                            {
                                                MLWord prevWord = mlWordArray[(int)number];
                                                if (prevWord.FontScale != fontRate)
                                                {
                                                    // 異なる長体率での上書きが生じるのでログ書き込み
                                                    logger.Log($"Row[{indexRow}] TextCast[{number}, {targetTextCastNameSingle}] Font Scale change[{prevWord.FontScale:F2} => {fontRate:F2}]");
                                                }
                                            }
                                            mlWordArray[(int)number] = new MLWord(number, fontRate, targetTextCastNameSingle, originalString);
                                        }

                                        // SDKのテキストキャストの辞書からキャスト番号を取得する。
                                        // キャスト名が見つかった場合のみ登録
                                        if (this.nameToIndexDictionary.ContainsKey(targetTextCastNameConnected))
                                        {
                                            // テキストキャスト番号
                                            uint number = this.nameToIndexDictionary[targetTextCastNameConnected];
                                            mlWordArray[(int)number] = new MLWord(number, fontRate, targetTextCastNameConnected, originalString);
                                        }
                                    }
                                }
                                finally
                                {
                                    Marshal.ReleaseComObject(sheetML);
                                    logger.Log("Multi Lang Sheet Closed.");
                                }
                                // Worksheet(MultiLang) block


                                // Worksheet(Non-MultiLang) block
                                var sheetSL = worksheets[MLTABLE_GET_LENGTH_SHEET_NAME_SINGLE];
                                try
                                {
                                    logger.Log("Single Lang Sheet Opened.");

                                    // シートの行数を測る
                                    int rowCount;
                                    var columns = sheetSL.Columns;
                                    var cols = columns[COL_BASIS_CHECK_ROW_LENGTH_SINGLE];
                                    var colsFound = cols.Find("*", SearchOrder: Excel.XlSearchOrder.xlByRows, SearchDirection: Excel.XlSearchDirection.xlPrevious);
                                    rowCount = colsFound.Row;
                                    Marshal.ReleaseComObject(colsFound);
                                    Marshal.ReleaseComObject(cols);
                                    Marshal.ReleaseComObject(columns);


                                    // 使用範囲を一括で二次元配列にコピー
                                    // Cells[r,c]を使ってアクセスすると、参照速度が極端に遅くなるため
                                    // 一度、参照範囲のセル値をコピーしておく
                                    Object[,] rangeArray;
                                    Excel.Range usedRange = sheetSL.Range[USE_RANGE_SINGLE + rowCount.ToString()];

                                    try
                                    {
                                        // 参照範囲のセルデータを一括コピー
                                        rangeArray = usedRange.Value;
                                    }
                                    finally { Marshal.ReleaseComObject(usedRange); }

                                    // 二次元配列に対してループを回す
                                    int lastRow = rangeArray.GetLength(0);
                                    for (int indexRow = 2; indexRow <= lastRow; indexRow++)
                                    {
                                        // キャスト名 (cast name)列
                                        string castName = (string)rangeArray[indexRow, COL_CAST_NAME_SINGLE];
                                        // 長体率列
                                        double fontRate = CellObjReadToRate(rangeArray[indexRow, COL_FONT_SCALE_SINGLE]);

                                        // パターン２（非多言語対応）
                                        // SDKのテキストキャストの中から探し出すキャスト名はエクセルシートで指定する文字列のまま
                                        // 空白ならばスキップ
                                        if (string.IsNullOrWhiteSpace(castName))
                                        {
                                            continue;
                                        }

                                        // 前後の空白を除去
                                        castName = castName.Trim();

                                        // SDKのテキストキャストの辞書からキャスト番号を取得する。
                                        // キャスト名が見つかった場合のみ登録
                                        if (this.nameToIndexDictionary.ContainsKey(castName))
                                        {
                                            // テキストキャスト番号
                                            uint number = this.nameToIndexDictionary[castName];

                                            // 既にキャスト番号に対応した長体率が登録されているかどうかを確認して
                                            // 登録されていれば、上書き処理をログ処理する
                                            if (mlWordArray[(int)number] != null)
                                            {
                                                MLWord prevWord = mlWordArray[(int)number];
                                                if (prevWord.FontScale != fontRate)
                                                {
                                                    // 異なる長体率での上書きが生じるのでログ書き込み
                                                    logger.Log($"Row[{indexRow}] TextCast[{number}, {castName}] Font Scale change[{prevWord.FontScale:F2} => {fontRate:F2}]");
                                                }
                                            }

                                            mlWordArray[(int)number] = new MLWord(number, fontRate, castName, string.Empty);
                                        }
                                    }

                                    // 出力コード生成
                                    CreateOutputScaleTable(mlWordArray);

                                    result = true;
                                }
                                finally
                                {
                                    Marshal.ReleaseComObject(sheetSL);
                                    logger.Log("Single Lang Sheet Closed.");
                                }
                                // Worksheet(Non-MultiLang) block

                            }
                            catch(Exception ex)
                            {
                                MessageBox.Show(ex.Message);
                            }
                            finally { Marshal.ReleaseComObject(worksheets); }
                            // Sheets block END
                        }
                        finally
                        {
                            if (oWorkbookMultiLang != null)
                            {
                                oWorkbookMultiLang.Close(false);
                            }
                            Marshal.ReleaseComObject(oWorkbookMultiLang);
                        }
                        // Workbook block (MultiLang) END
                    }
                    finally
                    {
                        Marshal.ReleaseComObject(oWBs);
                    }
                    // Workbooks block END
                }
                finally
                {
                    if (excelApp != null)
                    {
                        excelApp.Quit();
                    }
                    Marshal.ReleaseComObject(excelApp);
                }
                // Excel Application block END
            }
            catch
            {
                result = false;
            }

            return result;
        }

        private void CreateOutputScaleTable(MLWord[] mlWordArray)
        {
            const string TEXT_FONT_SCALE_TABLE_NAME_MULTI = "gTextRatioRevDataArray";

            // スクリプト全体テンプレート
            string strWholeScript = Properties.Resources.textcast_revision;


            // ========================================================================
            // Inside of Text Font Scale Data Table
            // ========================================================================
            // テーブル内データ定義用Builder
            StringBuilder sbTextCastDataTableInside = new StringBuilder();
            foreach (var mlWord in mlWordArray)
            {
                int castNumber = -1;
                double rate = -1.0;
                string infoStr = string.Empty;
                string castName = string.Empty;
                //string originalStrWithNL = string.Empty;

                if (mlWord != null)
                {
                    castNumber = (int)mlWord.No;
                    rate = (mlWord.FontScale <= 0.0) ? 1.0 : mlWord.FontScale;

                    string[] splitStrArray = mlWord.OriginalString.Split(new char[] { '\n' });
                    //originalStrWithNL = string.Join("\\n", splitStrArray);

                    infoStr = $" /* cnum = {mlWord.No} {mlWord.Name} */";
                    castName = mlWord.Name;
                }
                //sbTextCastDataTableInside.AppendLine($"\t{{{castNumber}, {rate:F2}F, \"{originalStrWithNL}\" }},{infoStr}");
                sbTextCastDataTableInside.AppendLine($"\t{{{castNumber}, {rate:F2}F, \"{castName}\"}},{infoStr}");
            }

            // テーブル内データ挿入
            // ================
            strWholeScript = strWholeScript.Replace("[TEXTCAST_REVISION_DATA]", sbTextCastDataTableInside.ToString());
            strWholeScript = strWholeScript.Replace("[TABLE_NAME]", TEXT_FONT_SCALE_TABLE_NAME_MULTI);
            strWholeScript = strWholeScript.Replace("[TABLE_SIZE]", mlWordArray.Length.ToString());


            // 最終出力
            this.OutputCode = strWholeScript;
        }




        public string CellObjReadToFont(object cellObj)
        {
            string result = null;
            if (cellObj is string)
            {
                result = (string)cellObj;
            }
            return result;
        }

        public int CellObjReadToUnsignedInteger(object cellObj)
        {
            int result = -1;
            if (cellObj is double)
            {
                result = (int)(double)cellObj;
            }
            else if (cellObj is int)
            {
                result = (int)cellObj;
            }
            if (result < 0)
            {
                result = -1;
            }

            return result;
        }

        public double CellObjReadToRate(object cellObj)
        {
            double result = -1.0;

            if (cellObj is double)
            {
                result = (double)cellObj;
            }
            else if (cellObj is int)
            {
                int rateInt = (int)cellObj;
                result = rateInt / 100.0;
            }
            else if (cellObj == null)
            {
                result = 1.0;
            }
            else if (cellObj is string)
            {
                if (!double.TryParse((string)cellObj, out result))
                {
                    result = 1.0;
                }
            }

            if (result < 0.0)
            {
                result = -1.0;
            }

            return result;
        }

        public string CellObjReadToString(object cellObj)
        {
            string result = string.Empty;

            if(cellObj is double)
            {
                result = ((double)cellObj).ToString();
            }
            else if(cellObj is int)
            {
                result = ((int)cellObj).ToString();
            }
            else if(cellObj == null)
            {
                /* do nothing */
            }
            else
            {
                result = (string)cellObj;
            }

            return result;
        }

        /// <summary>
        /// テキスト着せ替え用Excelファイル選択用ファイルダイアログの展開
        /// </summary>
        /// <param name="title">ダイアログの説明用文言</param>
        /// <returns>ファイルパス、（キャンセル時string.Empty）</returns>
        private string GetFileNameFromOpenFileDialog(string title)
        {
            string fileName = string.Empty;

            using (OpenFileDialog ofDialog = new OpenFileDialog())
            {
                ofDialog.Title = title;
                ofDialog.Filter = "xlsx files (*.xlsx)|*.xlsx";
                ofDialog.RestoreDirectory = true;

                if (ofDialog.ShowDialog() == DialogResult.OK)
                {
                    fileName = ofDialog.FileName;
                }
            }

            return fileName;
        }
    }
}

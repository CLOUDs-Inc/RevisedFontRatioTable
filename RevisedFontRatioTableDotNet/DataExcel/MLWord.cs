using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RevisedFontRatioTableDotNet.DataExcel
{
    /// <summary>
    /// Multi Language Word
    /// </summary>
    public class MLWord
    {
        /// <summary>
        /// 番号
        /// </summary>
        public UInt32 No { get; private set; }

        /// <summary>
        /// フォント長体率
        /// </summary>
        public double FontScale { get; private set; }

        /// <summary>
        /// テキストキャスト名
        /// </summary>
        public string Name { get; private set; }

        /// <summary>
        /// テキスト（改行コード込み）
        /// </summary>
        public string OriginalString { get; private set; }

        /// <summary>
        /// 非Multi Lang Sheet Flag(multi:0, non-multi:1)
        /// </summary>
        public int NonMultiLangFlag { get; private set; }

        public MLWord(UInt32 no, double fontScale, string name, string originalString, int nonMultiLangFlag)
        {
            this.No = no;
            this.FontScale = fontScale;
            this.Name = name;
            this.OriginalString = originalString;
            this.NonMultiLangFlag = nonMultiLangFlag;
        }
    }
}

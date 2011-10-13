#pragma once
#ifndef URASANDESU_NANONYM_STACKFRAME_H
#define URASANDESU_NANONYM_STACKFRAME_H

namespace Urasandesu { namespace NAnonym {

    class StackFrame
    {
    public:
        StackFrame() :
            m_hProcess(NULL),
            m_offset(0),
            m_symDisp(0),
            m_fileLineNum(0),
            m_fileColumnNum(0)
        { }
        
        void Init(HANDLE hProcess, DWORD offset)
        {
            m_hProcess = hProcess;
            m_offset = offset;
        }
        
        DWORD GetOffset()
        {
            return m_offset;
        }
        
        std::string const &GetModuleName()
        {
            if (m_modName == "")
            {
                IMAGEHLP_MODULE mod;
	            ::ZeroMemory(&mod, sizeof(IMAGEHLP_MODULE));
                mod.SizeOfStruct = sizeof(IMAGEHLP_MODULE);

                m_modName = ::SymGetModuleInfo(m_hProcess, m_offset, &mod) == TRUE ? 
                                                       mod.ImageName : "<Unknown Module>";
            }
            return m_modName;    
        }
        
        std::string const &GetSymbolName()
        {
            FillSymbolInfoIfNecessary();
            return m_symName;
        }
        
        DWORD GetSymbolDisplacement()
        {
            FillSymbolInfoIfNecessary();
            return m_symDisp;
        }
        
        std::string const &GetFileName()
        {
            FillFileLineInfoIfNecessary();
            return m_fileName;
        }
        
        DWORD GetFileLineNumber()
        {
            FillFileLineInfoIfNecessary();
            return m_fileLineNum;
        }
        
        DWORD GetFileColumnNumber()
        {
            FillFileLineInfoIfNecessary();
            return m_fileColumnNum;
        }

    private:        
        void FillSymbolInfoIfNecessary()
        {
            if (!HasGotSymbolInfo())
                FillSymbolInfo();
        }
        
        bool HasGotSymbolInfo()
        {
            return m_symName != "";
        }
        
        void FillSymbolInfo()
        {
	        BYTE pBuf[MAX_SYM_NAME + sizeof(IMAGEHLP_SYMBOL)];
            PIMAGEHLP_SYMBOL pSym = reinterpret_cast<PIMAGEHLP_SYMBOL>(pBuf);
	        ::ZeroMemory(pSym, sizeof(pBuf)); 

            pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
            pSym->MaxNameLength = MAX_SYM_NAME;

            m_symName = ::SymGetSymFromAddr(m_hProcess, m_offset, &m_symDisp, pSym) == TRUE ? 
                                                                pSym->Name : "<Unknown Symbol>";
        }

        void FillFileLineInfoIfNecessary()
        {
            if (!HasGotFileLineInfo())
                FillFileLineInfo();
        }
        
        bool HasGotFileLineInfo()
        {
            return m_fileName != "";
        }
        
        void FillFileLineInfo()
        {
            IMAGEHLP_LINE line;
	        ::ZeroMemory(&line, sizeof(IMAGEHLP_LINE)); 
            line.SizeOfStruct = sizeof(IMAGEHLP_LINE);

            m_fileName = ::SymGetLineFromAddr(m_hProcess, m_offset, &m_fileColumnNum, &line) == TRUE ? 
                                                                        line.FileName : "<Unknown Line>";
            m_fileLineNum = line.LineNumber;
        }

        HANDLE m_hProcess;
        DWORD m_offset;

        std::string m_modName;
        std::string m_symName;
        DWORD m_symDisp;
        std::string m_fileName;
        DWORD m_fileLineNum;
        DWORD m_fileColumnNum;
    };

}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_STACKFRAME_H
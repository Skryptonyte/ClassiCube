typedef struct _CRYPTOAPI_BLOB {
	DWORD cbData;
	BYTE* pbData;
} DATA_BLOB;

static BOOL (WINAPI *_CryptProtectData  )(DATA_BLOB* dataIn, PCWSTR dataDescr, PVOID entropy, PVOID reserved, PVOID promptStruct, DWORD flags, DATA_BLOB* dataOut);
static BOOL (WINAPI *_CryptUnprotectData)(DATA_BLOB* dataIn, PWSTR* dataDescr, PVOID entropy, PVOID reserved, PVOID promptStruct, DWORD flags, DATA_BLOB* dataOut);

static void Crypt32_LoadDynamicFuncs(void) {
	static const struct DynamicLibSym funcs[] = {
		DynamicLib_Sym(CryptProtectData), DynamicLib_Sym(CryptUnprotectData)
	};

	static const cc_string crypt32 = String_FromConst("CRYPT32.DLL");
	static void* crypt32_lib;
	
	if (crypt32_lib) return;
	DynamicLib_LoadAll(&crypt32, funcs, Array_Elems(funcs), &crypt32_lib);
}
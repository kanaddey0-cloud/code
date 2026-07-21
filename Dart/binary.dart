// import 'dart:io';
// dependencies: crc32: ^1.0.0
// import 'package:crc32/crc32.dart';

// void main() {
//   File file = File("data.rkd");

//   List<int> bytes = file.readAsBytesSync();

//   int checksum = crc32(bytes);

//   print("CRC32: $checksum");
// } 




// import 'dart:io';
// import 'dart:convert';

// List<int> compressData(List<int> data) {
//   return GZipCodec().encode(data);
// }

// List<int> decompressData(List<int> data) {
//   return GZipCodec().decode(data);
// }

// void main() {
//   List<int> original = [65, 66, 67, 68, 69];

//   List<int> compressed = compressData(original);

//   List<int> decompressed = decompressData(compressed);

//   print(original);
//   print(compressed);
//   print(decompressed);
// }




// dependencies: cryptography: ^2.7.0
// import 'package:cryptography/cryptography.dart';

// final algorithm = AesGcm.with256bits();

// 🔐 AES-256
// Future<List<int>> encryptData(List<int> data, SecretKey key) async {
//   final secretBox = await algorithm.encrypt(
//     data,
//     secretKey: key,
//   );
  
//   return secretBox.concatenation();
// }

// // 🔓 Decrypt
// Future<List<int>> decryptData(List<int> encrypted, SecretKey key) async {
//   final secretBox = SecretBox.fromConcatenation(
//     encrypted,
//     nonceLength: 12,
//     macLength: 16,
//   );

//   return await algorithm.decrypt(
//     secretBox,
//     secretKey: key,
//   );
// }

// void main() async {
//   final key = await algorithm.newSecretKey();

//   List<int> data = [65, 66, 67];

//   List<int> encrypted =
//       await encryptData(data, key);

//   print(encrypted);

//   List<int> decrypted =
//       await decryptData(encrypted, key);

//   print(decrypted);
// }




// import 'dart:ffi';

// final dylib = DynamicLibrary.open('math.dll');

// final add = dylib.lookupFunction<
//     Int32 Function(Int32, Int32),
//     int Function(int, int)
// >('add');

// void main() {
//   print(add(10, 20));
// }




// import 'dart:io';
// import 'package:receive_sharing_intent/receive_sharing_intent.dart';

// void initSharedFiles() {
//   // Get files when app is opened from outside (share/open intent)
//   ReceiveSharingIntent.instance.getInitialMedia().then((files) async {

//     // Step 1: filter only .rkd files & remove fake ones
//     final rkdFiles = files.where((f) {
//       return f.path.endsWith('.rkd') &&
//              (f.mimeType == 'application/octet-stream' ||
//               f.mimeType == null);             // can be rename file.jpg → file.rkd
//     }).toList();

//     if (rkdFiles.isEmpty) { print('No .rkd file found');  return; }

//     // Step 2: debug print
//     for (final file in rkdFiles) print('REAL RKD file: ${file.path}');

//     // Step 3: read first valid file
//     final file = File(rkdFiles.first.path);     // Take first valid .rkd file
//     final content = await file.readAsString();  // Read file content as text
//     print(content);
//   });
// }

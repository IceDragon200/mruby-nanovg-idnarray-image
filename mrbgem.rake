MRuby::Gem::Specification.new('mruby-nanovg-idnarray-image') do |spec|
  spec.license = 'MIT'
  spec.authors = ['Corey Powell']
  spec.version = '1.0.0'
  spec.summary = 'Enables the usage of NArray for image data.'
  spec.description = 'Enables the usage of NArray for image data.'
  spec.homepage = 'https://github.com/IceDragon200/mruby-nanovg-idnarray-image'
  # This is an extension for nanovg using idnarray
  spec.add_dependency 'mruby-nanovg'
  spec.add_dependency 'mruby-idnarray'
end
